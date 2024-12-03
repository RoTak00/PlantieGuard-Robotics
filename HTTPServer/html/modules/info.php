<?php

$json = [];

// Offers info about self. Index page


$json['version'] = $VERSION;
$json['appname'] = $APP_NAME;
$json['timestamp'] = date("Y-m-d H:i:s");

echo json_encode($json);
