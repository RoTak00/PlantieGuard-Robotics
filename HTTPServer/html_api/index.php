<?php

require_once 'config.php';
require_once 'inc/db-config.php';
require_once 'inc/functions.php';
require_once 'inc/db-functions.php';

if ($_SERVER['REQUEST_METHOD'] == 'GET') {

    if (isset($_GET['action'])) {
        $action = $_GET['action'];

        switch ($action) {
            case 'ack':
                include 'modules/ack.php';
                break;

            case 'data':
                include 'modules/data.php';
                break;

            default:
                include 'modules/info.php';
                break;
        }
    } else {
        include 'modules/info.php';
        exit();
    }
} else {
    include 'modules/info.php';
    exit();
}


