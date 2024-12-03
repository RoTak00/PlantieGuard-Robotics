# Variables
COMPOSE_FILE = docker-compose.yml
PROJECT_NAME = plantieguard

# Build the Docker images
build:
	docker-compose -f $(COMPOSE_FILE) build

# Start the containers
up:
	docker-compose -f $(COMPOSE_FILE) up -d

# Stop the containers
stop:
	docker-compose -f $(COMPOSE_FILE) stop

# Remove the containers
clean:
	docker-compose -f $(COMPOSE_FILE) down

# Rebuild and restart everything
rebuild: clean build up

# View logs
logs:
	docker-compose -f $(COMPOSE_FILE) logs -f
