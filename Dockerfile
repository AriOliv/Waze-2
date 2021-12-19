FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get -y update && \
    apt-get -y install apache2 systemctl build-essential && \
    sed -i "$ a\ServerName 127.0.0.1" /etc/apache2/apache2.conf

COPY / /var/www/files

RUN chown -R root /var/www/files

COPY /auxiliares/files.conf /etc/apache2/sites-available/

RUN service apache2 start && \
    a2ensite files.conf && a2dissite 000-default.conf && \
    apache2ctl configtest && \
    systemctl restart apache2 && \
    a2enmod cgid && \
    systemctl restart apache2

COPY /auxiliares/cgi-enabled.conf /etc/apache2/conf-available

RUN a2enconf cgi-enabled && \
    systemctl restart apache2 && \
    g++ /var/www/files/backend/main.cpp -o /var/www/files/backend/main.cgi && \
    chmod 755 /var/www/files/backend/main.cgi

ENTRYPOINT ["/usr/sbin/apache2ctl"]

CMD ["-DFOREGROUND"]
