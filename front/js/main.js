var drawLayer = new L.FeatureGroup();
drawLayer.addTo(map);

class Path {
    // Executando o fecth da API
    constructor(y1, x1, y2, x2, algoritmo=1, alternative_paths=0, by_travel_time=1) {
        // Usando a API para obter o caminho
        // A API acessa o manin.cgi da máquina virtual na nuvem
        this.alternative_paths = alternative_paths;
        if(by_travel_time == 1){
            this.metric = "min"
            this.metric_name = "Tempo de viagem:"
            this.divisor = 60
        }
        else{
            this.metric = "km"
            this.metric_name = "Distância:"
            this.divisor = 1000
        }
        fetch(`../../backend/main.cgi?${y1};${x1};${y2};${x2};${algoritmo};${by_travel_time}`)
            .then(this.onSucess.bind(this))
    }
    async onSucess(response) {
        response.json().then(this.onProcessed.bind(this));
    }
    onProcessed(json) {
        this.node_path = json
        console.log(this.node_path)
        
        let nav_info = document.getElementById("dist-value")
        nav_info.innerHTML = ""
        let dist_info = document.createElement("p")

        dist_info = `${this.metric_name} ${Math.round(json["distancia"]/this.divisor)} ${this.metric}`
        let runtime = document.createElement("p")

        runtime.textContent = `Runtime: ${json["runtime"]}`
        nav_info.append(dist_info)
        nav_info.append(runtime)
        if (this.alternative_paths == 1) {
            this.draw_points_by_id();
            console.log("Rodando o alternativities")
        }
        else if (this.alternative_paths == 0) {
            this.draw_path_by_id();
            console.log("Rodando o single source")
        }
    }
    draw_points_by_id() {
        this.draw_path_by_id();
        for (const node of this.node_path["considered"]) {
            var pontos = new L.circle(new L.LatLng(node_coord[node - 1][1], node_coord[node - 1][2]), {
                color: "blue",
                opacity: 1,
                radius: 10,
            });
            // Add os pontos ao conjunto drawLayer
            drawLayer.addLayer(pontos)
            // Implementar o setTimeout para os pontos
            //window.setTimeout(drawLayer.addLayer(pontos), 3000);
        }
    }
    // Atual função que desenha o caminho através dos ids
    draw_path_by_id() {
        // Esta função itera sobre cada par de nós do caminho
        console.log(this.node_path["path"])
        for (let index = 1; index < this.node_path["path"].length; index++) {
            const id_from = this.node_path["path"][index - 1];
            const id_to = this.node_path["path"][index];
            // Essa função desenha o caminho entre dois nós vizinhos
            this.write_one_edge_by_id(id_from, id_to)
        }
    }
    // Nessa função é desenhado cada caminho testado pelo algoritmo
    // Função que desenha o caminho entre dois nós vizinhos
    write_one_edge_by_id(id_to, id_from) {
        console.log("Rodando o write path by id")
        let id_from_neighbors = streets2[id_from]
        let element;
        let edge;
        // Coletando o geojson de cada nó
        for (let index = 0; index < id_from_neighbors.length; index++) {
            // Acessando a lista de vizinhos do id_to
            element = id_from_neighbors[index];
            // Iterando sobre os vizinhos do id_to para encontrar o id_from especificado
            if (element["features"][0]["properties"]["v"] == id_to) {
                // Definindo o geojson correto
                edge = element;
            }
        }
        // Após a coleta do geojson
        // Adicionando-o ao desenho do mapa
        var desenho = new L.geoJSON(edge,
            {
                // Aqui é definido o estilo do caminho
                style: function (feature) {
                    return {
                        stroke: true,
                        color: "red",
                        weight: 5
                    }
                }
            });
        // Add o traçado ao conjunto drawLayer
        drawLayer.addLayer(desenho);
        // Centraliza a rota
        map.flyToBounds(drawLayer.getBounds())
    }
}

map.on('click', add_path);
// Variável que armezena as coordenadas
var coordenadas = []
let x1; let y1; let x2; let y2;
async function add_path(e) {
    coordenadas.push(e.latlng);
    if (coordenadas.length == 1) {   
        startMarker.setLatLng(coordenadas[0]); 
        clickZoom(e);
        drawLayer.clearLayers(); 
        map.removeLayer(destinMarker); 
    }
    if (coordenadas.length == 2) {
        console.log(coordenadas);
        x1 = coordenadas[0]['lng']
        y1 = coordenadas[0]['lat']
        x2 = coordenadas[1]['lng']
        y2 = coordenadas[1]['lat']
        startMarker.setLatLng(coordenadas[0]); 
        destinMarker.setLatLng(coordenadas[1]);
        destinMarker.addTo(map);
        new Path(y1, x1, y2, x2, algoritmo = algoritmoSelected, alternative_paths = showPoints, by_travel_time = showTime);
        coordenadas = [];
        localStorage.clear();
    }
}

// Add path from search bar
async function add_path_sb(marker) {
    //coordenadas.push(marker.getLatLng());
    if (coordenadas.length == 1 || coordenadas[0] == null) {   
        coordenadas[0] = startMarker.getLatLng(); 
        selZoom(coordenadas[0]);
        drawLayer.clearLayers();
        map.removeLayer(destinMarker);  
        console.log("epa");
    }
    if (coordenadas[1] != null && coordenadas[0] != null) {
        console.log(coordenadas[0] == null);
        console.log("opa");
        x1 = coordenadas[0]['lng']
        y1 = coordenadas[0]['lat']
        x2 = coordenadas[1]['lng']
        y2 = coordenadas[1]['lat']
        startMarker.setLatLng(coordenadas[0]); 
        destinMarker.setLatLng(coordenadas[1]);
        destinMarker.addTo(map);
        drawLayer.clearLayers();    
        new Path(y1, x1, y2, x2, algoritmo = algoritmoSelected, alternative_paths = showPoints, by_travel_time = showTime);
        coordenadas = [];
        localStorage.clear();
    }
}

