<?php
$host = 'db'; // Matches the service name in docker-compose.yml
$user = 'plantieguard_user';
$password = 'password';
$dbname = 'plantieguard';

// Create connection
$conn = new mysqli($host, $user, $password, $dbname);

// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
echo "Connected successfully to MySQL!";
?>