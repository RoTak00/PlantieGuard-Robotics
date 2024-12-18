<?php

class CommonNavigationController extends BaseController
{

    public function index($settings = [])
    {

        $this->response->addStyle('/resources/css/common/navigation.css');
        $data = [];

        $data['page_alias'] = $settings['page_alias'] ?? 'index';

        $data['notifications'] = $this->loadController('common/notification');

        return $this->loadView('common/navigation.php', $data);
    }
}