<div class="container">
    <div class="row">
        <div class="col-md-12">
            <h3>Plantie History</h3>
        </div>
    </div>


    <div class="row">
        <div class="col-xs-4 col-md-3">
            <strong>Humidity</strong>
        </div>
        <div class="col-xs-4 col-md-3">
            <strong>Soil Humidity</strong>
        </div>
        <div class="col-xs-4 col-md-3">
            <strong>Temperature</strong>
        </div>
        <div class="col-xs-4 col-md-3">
            <strong>Date</strong>
        </div>
    </div>

    <?php foreach ($device_data as $device_data_entry) { ?>
        <div class="row" style="margin-top: 5px;">
            <div class="col-xs-4 col-md-3">
                <?= $device_data_entry['humidity_linear'] ?>
            </div>
            <div class="col-xs-4 col-md-3">
                <?= $device_data_entry['humidity_soil_linear'] ?>
            </div>
            <div class="col-xs-4 col-md-3">
                <?= $device_data_entry['temperature_linear'] ?>
            </div>
            <div class="col-xs-4 col-md-3">
                <?= $device_data_entry['date_added_format'] ?>
            </div>
        </div>

    <?php } ?>
</div>