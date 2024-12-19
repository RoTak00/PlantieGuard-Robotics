<?php

class AccountRegisterController extends BaseController
{
    public $error = [];

    public function index()
    {
        if ($this->user->LoggedIn()) {
            return $this->response->redirect('common/home');
        }

        if (!empty($this->session->data['uuid'])) {
            $uuid = $this->session->data['uuid'];
        } else if (!empty($this->session->cookie['uuid'])) {
            $uuid = $this->session->cookie['uuid'];
        }

        return $this->response->redirect('account/register/uuid/' . urlencode($uuid));
    }

    public function uuid($params)
    {

        if ($this->user->LoggedIn()) {
            return $this->response->redirect('common/home');
        }

        $uuid = null;
        if (!empty($params[0])) {
            $uuid = $params[0];
        } else if (!empty($this->session->data['uuid'])) {
            $uuid = $this->session->data['uuid'];
        } else if (!empty($this->session->cookie['uuid'])) {
            $uuid = $this->session->cookie['uuid'];
        }

        // We must have a token to register
        if (empty($params[0])) {
            $this->notification->set('error', 'Please complete the setup process of your PlantieGuard device first!');
            return $this->response->redirect('account/login');
        }

        // Check that the token is a uuid found in the database

        $uuid = $params[0];

        $this->loadModel('account/uuid');
        if (!$this->model_account_uuid->check_uuid($uuid)) {
            $this->notification->set('error', 'Please complete the setup process of your PlantieGuard device first!');
            return $this->response->redirect('account/login');
        }

        $this->session->data['uuid'] = $uuid;
        $this->session->setCookie('uuid', $uuid);

        // Check that the token is not used by another user 
        if ($this->model_account_uuid->get_user_by_uuid($uuid)) {
            $this->notification->set('error', 'You\'ve already created an account. Please log in!');
            return $this->response->redirect('account/login');
        }

        if ($this->request->server['REQUEST_METHOD'] == 'POST') {

            if ($this->validateForm()) {
                $this->user->register($this->request->post['username'], $this->request->post['email'], $this->request->post['password']);

                // log in the user
                $this->user->login($this->request->post['email'], $this->request->post['password']);
                $this->model_account_uuid->set_uuid($uuid);

                $this->notification->set('success', 'You\'ve successfully created an account!');
                return $this->response->redirect('common/home');
            }

        }

        $data = [];

        $data['error'] = $this->error;


        $data['username'] = '';
        if (isset($this->request->post['username'])) {
            $data['username'] = $this->request->post['username'];
        }

        $data['email'] = '';
        if (isset($this->request->post['email'])) {
            $data['email'] = $this->request->post['email'];
        }

        $data['footer'] = $this->loadController('common/footer');
        $data['navigation'] = $this->loadController('common/navigation');


        $head_settings = ['page_title' => 'PlantieGuard - Register'];
        $data['head'] = $this->loadController('common/head', $head_settings);
        return $this->loadView('account/register.php', $data);
    }

    public function validateForm()
    {
        if (empty($this->request->post['username'])) {
            $this->error['username'] = 'Username is required!';
        }

        // check that the username is not taken
        $this->loadModel('account/user');
        if ($this->model_account_user->get_user_by_username($this->request->post['username'])) {
            $this->error['username'] = 'Username is already taken!';
        }

        if (empty($this->request->post['email'])) {
            $this->error['email'] = 'Email is required!';
        }

        // filter var 
        if (!filter_var($this->request->post['email'], FILTER_VALIDATE_EMAIL)) {
            $this->error['email'] = 'Email is invalid!';
        }

        // check that the email is not taken
        if ($this->model_account_user->get_user_by_email($this->request->post['email'])) {
            $this->error['email'] = 'Email is already taken!';
        }

        if (empty($this->request->post['password'])) {
            $this->error['password'] = 'Password is required!';
        }

        // password at least 6 characters
        if (strlen($this->request->post['password']) < 6) {
            $this->error['password'] = 'Password must be at least 6 characters!';
        }

        if (empty($this->request->post['confirm_password'])) {
            $this->error['confirm_password'] = 'Confirm Password is required!';
        }

        if ($this->request->post['password'] != $this->request->post['confirm_password']) {
            $this->error['confirm_password'] = 'Passwords do not match!';
        }

        if (empty($this->error)) {
            return true;
        }

        return false;
    }



}