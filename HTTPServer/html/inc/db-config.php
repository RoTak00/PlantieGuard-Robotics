<?php


// Create connection
$conn = new mysqli($DB_HOST, $DB_USER, $DB_PASSWORD, $DB_NAME);

// Change character set to utf8
$conn->set_charset("utf8");
mysqli_report(MYSQLI_REPORT_ERROR | MYSQLI_REPORT_STRICT);

// exception mdoe 


// Check connection
if ($conn->connect_error) {
    http_response_code(500);
    $json = [];
    $json['err_code'] = 'I_ERROR';
    $json['err_msg'] = 'Internal Server Error';
    echo json_encode($json);
    exit();
}
?>