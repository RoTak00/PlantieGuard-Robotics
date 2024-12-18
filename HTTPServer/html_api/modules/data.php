<?php

$json = [];

// The Arduino board will send its token whenever it is making a request to the server
// It will send its UUID which is used to identify the device, but it must send an ack first.
// Server will receive sensor data such as temperature, humidity, soil humidity, tank level
// Server will send back ack and a special value if user has requested to water the plant, plus the duration

if (!isset($_GET['token'])) {
    http_response_code(400);
    $json['err_code'] = 'NO_TOKEN';
    $json['err_msg'] = 'Missing UUID Token.';
    echo json_encode($json);
    exit();
}

if (!validateUUID($_GET['token'])) {
    http_response_code(400);
    $json['err_code'] = 'INVALID_TOKEN';
    $json['err_msg'] = 'Invalid UUID Token.';
    echo json_encode($json);
    exit();
}

$token = $_GET['token'];


$device = getExistsDevice($token);


if (!$device) {
    http_response_code(403);
    $json['err_code'] = 'NOT_REGISTERED';
    $json['err_msg'] = 'Unauthorized User';
    echo json_encode($json);
    exit();
}

// parse the incoming data
$temperature = $_GET['temperature'] ?? null;
$humidity = $_GET['humidity'] ?? null;
$humidity_soil = $_GET['humidity_soil'] ?? null;
$tank_level = $_GET['tank_level'] ?? null;
$action_treated = $_GET['done_id'] ?? null;

enum Sensors: int
{
    case Temperature = 1;
    case Humidity = 2;
    case Humidity_Soil = 4;
    case Tank_Level = 8;
}
$missing_values = 0;

if ($temperature == null) {
    $temperature = getLastValidSensorParam($token, "temperature");
    $missing_values = $missing_values | Sensors::Temperature->value;
}

if ($humidity == null) {
    $humidity = getLastValidSensorParam($token, "humidity");
    $missing_values = $missing_values | Sensors::Humidity->value;
}

if ($humidity_soil == null) {
    $humidity_soil = getLastValidSensorParam($token, "humidity_soil");
    $missing_values = $missing_values | Sensors::Humidity_Soil->value;
}

if ($tank_level == null) {
    $tank_level = getLastValidSensorParam($token, "tank_level");
    $missing_values = $missing_values | Sensors::Tank_Level->value;
}


saveSensorData($token, $temperature, $humidity, $humidity_soil, $tank_level, $missing_values);

if ($action_treated != null) {
    updateActionStatus($token, $action_treated);
}

$action = getActiveAction($token);



$json['version'] = $VERSION;
$json['appname'] = $APP_NAME;
$json['timestamp'] = date("Y-m-d H:i:s");
$json['token'] = $token;
$json['temperature'] = $temperature;
$json['humidity'] = $humidity;
$json['humidity_soil'] = $humidity_soil;
$json['tank_level'] = $tank_level;
$json['missing_values'] = $missing_values;
$json['action'] = 'data';

if ($action) {
    $json['action_id'] = $action['action_id'];
    $json['action'] = $action['action'];
    $json['duration'] = $action['duration'];
}


echo json_encode($json);
exit();

