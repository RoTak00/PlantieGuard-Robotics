<?php

class DataDataController extends BaseController
{
    public function current($setting)
    {
        $device_data = $setting['device_data'];

        $date_added = $device_data['date_added'];

        $data = [];

        $data['humidity_soil_linear'] = $this->loadController('module/linear_view', ['value' => $device_data['humidity_soil'], 'color' => 'green', 'title' => 'Soil Humidity']);
        $data['humidity_linear'] = $this->loadController('module/linear_view', ['value' => $device_data['humidity'], 'color' => 'green', 'title' => 'Humidity']);
        $data['temperature_linear'] = $this->loadController('module/linear_view', ['value' => $device_data['temperature'], 'color' => 'green', 'title' => 'Temperature', 'min' => 10, 'max' => 40, 'symbol' => '°C']);

        $data['date_added'] = $date_added;
        $data['date_added_format'] = date('d-m-Y H:i:s', strtotime($date_added));

        return $this->loadView('data/current_data_view.php', $data);



    }

    public function history($setting = [])
    {
        $user_id = $this->user->getId();
        if (!empty($setting['user_id'])) {
            $user_id = $setting['user_id'];
        }

        $limit = 50;
        if (!empty($setting['limit'])) {
            $limit = $setting['limit'];
        }


        $this->loadModel('data/data');

        $device_data = $this->model_data_data->getDeviceData($limit, 0);

        $device_data = array_map(function ($data_entry) {

            $data_entry['date_added_format'] = date('d-m-Y H:i:s', strtotime($data_entry['date_added']));

            $data_entry['humidity_soil_linear'] = $this->loadController('module/linear_view', ['value' => $data_entry['humidity_soil'], 'color' => 'green']);
            $data_entry['humidity_linear'] = $this->loadController('module/linear_view', ['value' => $data_entry['humidity'], 'color' => 'green']);
            $data_entry['temperature_linear'] = $this->loadController('module/linear_view', ['value' => $data_entry['temperature'], 'color' => 'green', 'min' => 10, 'max' => 40, 'symbol' => '°C']);
            return $data_entry;

        }, $device_data);

        $data = [];

        $data['device_data'] = $device_data;

        return $this->loadView('data/history_data_view.php', $data);



    }
}