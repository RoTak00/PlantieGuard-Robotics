<?php

class CommonHomeController extends BaseController
{


    public function index()
    {
        $data = [];

        $data['footer'] = $this->loadController('common/footer');
        $data['navigation'] = $this->loadController('common/navigation');


        $head_settings = ['page_title' => 'PlantieGuard - Home'];
        $data['head'] = $this->loadController('common/head', $head_settings);
        return $this->loadView('common/home.php', $data);
    }
}