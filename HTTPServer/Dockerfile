# Use the official PHP image with FPM support
FROM php:8.2-fpm

# Install Nginx and necessary PHP extensions
RUN apt-get update && apt-get install -y nginx libpng-dev libjpeg-dev libfreetype6-dev libonig-dev libxml2-dev zip unzip git curl mariadb-client \
    && docker-php-ext-install pdo_mysql mysqli gd \
    && rm -rf /var/lib/apt/lists/*

# Copy custom Nginx configuration
COPY nginx.conf /etc/nginx/nginx.conf

# Copy website files
COPY html /usr/share/nginx/html

# Expose port 80
EXPOSE 80

# Start PHP-FPM and Nginx
CMD ["sh", "-c", "php-fpm & nginx -g 'daemon off;'"]
