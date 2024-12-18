<?php

class CommonErrorController extends BaseController
{

    public function index()
    {
        $data = [];

        $data['footer'] = $this->loadController('common/footer');

        $navigation_settings = ['page_alias' => 'error'];
        $data['navigation'] = $this->loadController('common/navigation', $navigation_settings);

        $head_settings = ['page_title' => 'Page not found!'];
        $data['head'] = $this->loadController('common/head', $head_settings);
        return $this->loadView('common/error.php', $data);
    }
}