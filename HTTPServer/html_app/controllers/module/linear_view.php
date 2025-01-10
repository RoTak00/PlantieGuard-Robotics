<?php
class ModuleLinearViewController extends BaseController
{
    public function index($setting)
    {

        $this->response->addStyle('/resources/css/module/linear_view.css');

        $min = 0;
        if (!empty($setting['min'])) {
            $min = $setting['min'];
        }

        $max = 100;
        if (!empty($setting['max'])) {
            $max = $setting['max'];
        }

        if ($setting['value'] > $max) {
            $setting['value'] = $max;
        }

        if ($setting['value'] < $min) {
            $setting['value'] = $min;
        }

        // map the value to a percentage
        $percentage = round((($setting['value'] - $min) / ($max - $min)) * 100);
        $setting['percentage'] = $percentage;

        $symbol = '%';
        if (!empty($setting['symbol'])) {
            $symbol = $setting['symbol'];
        }
        $setting['symbol'] = $symbol;

        return $this->loadView('module/linear_scale_view.php', $setting);
    }
}