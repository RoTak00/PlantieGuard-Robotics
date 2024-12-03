<?php

$json = [];

// The Arduino board will send an ACK when it first connects to the server, to check connection
// It will send its UUID which is used to identify the device, allowing for continuity on stop / restart or wifi change
// Server will send a different ack based on new device or existent device

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

$json['version'] = $VERSION;
$json['appname'] = $APP_NAME;
$json['timestamp'] = date("Y-m-d H:i:s");
$json['action'] = 'ack';
$json['token'] = $token;


$result = getExistsDevice($token);


http_response_code(200);
if ($result) {
    $json['ack'] = 'EXISTS';
} else {
    saveDevice($token);
    $json['ack'] = 'NEW';
}

echo json_encode($json);
exit();

