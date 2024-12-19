<?php

class DataDataController extends BaseController
{
    public function current($setting)
    {
        $device_data = $setting['device_data'];

        $humidity = $device_data['humidity'];
        $humidity_soil = $device_data['humidity_soil'];
        $temperature = $device_data['temperature'];
        $date_added = $device_data['date_added'];

        $data = [];

        $data['humidity'] = $humidity;
        $data['humidity_soil'] = $humidity_soil;
        $data['temperature'] = $temperature;
        $data['date_added'] = $date_added;
        $data['date_added_format'] = date('d-m-Y H:i:s', strtotime($date_added));



        return $this->loadView('data/current_data_view.php', $data);



    }
}