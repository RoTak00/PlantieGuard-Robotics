<?php

function getExistsDevice($token)
{
    global $conn;
    $sql = "SELECT * FROM pg_devices WHERE token = '" . $conn->real_escape_string($token) . "'";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        return $result->fetch_assoc();
    } else {
        return false;
    }
}

function saveDevice($token)
{
    global $conn;
    $sql = "INSERT INTO pg_devices (token, ip, device, date_added) VALUES
     ('" . $conn->real_escape_string($token) . "', '" . $_SERVER['REMOTE_ADDR'] . "', '" . $_SERVER['HTTP_USER_AGENT'] . "', NOW())";
    $conn->query($sql);
}

function getLastValidSensorParam($token, $param)
{
    global $conn;
    $sql = "SELECT " . $conn->real_escape_string($param) . " FROM pg_data WHERE token = '" . $conn->real_escape_string($token) . "' ORDER BY id DESC LIMIT 1";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        return $result->fetch_assoc()[$param];
    } else {
        return null;
    }
}

function saveSensorData($token, $temperature, $humidity, $humidity_soil, $tank_level, $missing_values)
{
    global $conn;
    $sql = "INSERT INTO pg_data (token, temperature, humidity, humidity_soil, tank_level, missing_values, date_added) VALUES
     ('" . $conn->real_escape_string($token) . "', '" . (float) $temperature
        . "', '" . (float) $humidity . "', '" . (float) $humidity_soil
        . "', '" . (float) $tank_level . "', '" . (int) $missing_values . "', NOW())";

    $conn->query($sql);
}

function updateActionStatus($token, $action_treated)
{
    global $conn;
    $sql = "UPDATE pg_action SET treated_on = NOW() WHERE token = '" . $conn->real_escape_string($token) . "' AND action_id = '" . (int) $action_treated . "'";
    $conn->query($sql);
}

function getActiveAction($token)
{
    global $conn;
    $sql = "SELECT action_id, action, duration FROM pg_action WHERE token = '" . $conn->real_escape_string($token) . "' AND treated_on IS NULL";
    $result = $conn->query($sql);

    if ($result->num_rows > 0) {
        return $result->fetch_assoc();
    } else {
        return false;
    }
}