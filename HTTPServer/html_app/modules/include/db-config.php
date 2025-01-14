<?php

// display errors
ini_set('display_errors', $PHP_DISPLAY_ERRORS);
ini_set('display_startup_errors', $PHP_DISPLAY_STARTUP_ERRORS);

// default timezone
date_default_timezone_set($DEFAULT_TIMEZONE);

// Get Current date, time
$current_time = time();
$current_date = date("Y-m-d H:i:s", $current_time);

$ip = $_SERVER['REMOTE_ADDR'];
$geo_data = file_get_contents("http://www.geoplugin.net/json.gp?ip={$ip}");
$geo_data = json_decode($geo_data, true);
$user_timezone = $geo_data['geoplugin_timezone'] ?? "UTC";


// Create database connection
$conn = new mysqli($SERVERNAME, $USERNAME, $PASSWORD, $DATABASE);
$conn->set_charset("utf8mb4");

// Check connection
if ($conn->connect_error) {
    //AddAlert("Eroare la conectare la baza de date.", "danger");
    die("Connection failed: " . $conn->connect_error);
}

$conn->query('set character_set_client=utf8');
$conn->query('set character_set_connection=utf8');
$conn->query('set character_set_results=utf8');
$conn->query('set character_set_server=utf8');


?>