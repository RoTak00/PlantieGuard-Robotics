<?php

class CommonHeadController extends BaseController
{

    public function index($setting = [])
    {
        global $HOST;
        $this->response->addStyle("/resources/inc/bootstrap.min.css", [], 1);
        $this->response->addScript("/resources/inc/bootstrap.bundle.min.js", [], 1);
        $this->response->addScript("/resources/inc/jquery.js", [], 1);

        $this->response->addStyle("/resources/css/common/styles.css");

        $data = [];

        $data['styles'] = $this->response->getStyles();
        $data['scripts'] = $this->response->getScripts();

        $this->response->addMeta('og:site_name', 'PlantieGuard');
        $this->response->addMeta('og:url', $HOST . '/' . $this->request->get['path']);

        $data['meta'] = $this->response->getMeta();


        $data['title'] = $setting['page_title'] ?? 'PlantieGuard';


        return $this->loadView('common/head.php', $data);
    }
}