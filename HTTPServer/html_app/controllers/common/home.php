<?php

class CommonHomeController extends BaseController
{


    public function index()
    {

        if ($this->user->LoggedIn() == false) {
            return $this->response->redirect('account/login');
        }

        $data = [];

        $this->loadModel('data/data');

        $device_data = $this->model_data_data->getMostRecentDataEntry();

        if (!empty($device_data)) {
            $data['current_device_data'] = $this->loadController('data/data/current', ['device_data' => $device_data]);
        }

        $data['device_history_data'] = $this->loadController('data/data/history');

        $data['footer'] = $this->loadController('common/footer');
        $data['navigation'] = $this->loadController('common/navigation');


        $head_settings = ['page_title' => 'PlantieGuard - Home'];
        $data['head'] = $this->loadController('common/head', $head_settings);
        return $this->loadView('common/home.php', $data);
    }
}