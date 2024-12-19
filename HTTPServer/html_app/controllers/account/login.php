<?php

class AccountLoginController extends BaseController
{
    public $error = [];

    public function index()
    {
        if ($this->user->LoggedIn()) {
            return $this->response->redirect('common/home');
        }

        if ($this->request->server['REQUEST_METHOD'] == 'POST') {

            if ($this->validateForm()) {

                // log in the user
                if (!$this->user->login($this->request->post['email'], $this->request->post['password'])) {
                    $this->notification->set('error', 'E-mail or password is incorrect!');
                } else {
                    $this->notification->set('success', 'You\'ve successfully logged in!');
                    return $this->response->redirect('common/home');
                }
            }

        }

        $data = [];

        $data['error'] = $this->error;

        $data['email'] = '';
        if (isset($this->request->post['email'])) {
            $data['email'] = $this->request->post['email'];
        }

        $data['footer'] = $this->loadController('common/footer');
        $data['navigation'] = $this->loadController('common/navigation');


        $head_settings = ['page_title' => 'PlantieGuard - Login'];
        $data['head'] = $this->loadController('common/head', $head_settings);
        return $this->loadView('account/login.php', $data);
    }

    public function validateForm()
    {
        if (empty($this->request->post['email'])) {
            $this->error['email'] = 'Email is required!';
        }

        // filter var 
        if (!filter_var($this->request->post['email'], FILTER_VALIDATE_EMAIL)) {
            $this->error['email'] = 'Email is invalid!';
        }

        if (empty($this->request->post['password'])) {
            $this->error['password'] = 'Password is required!';
        }

        if (empty($this->error)) {
            return true;
        }

        return false;
    }



}