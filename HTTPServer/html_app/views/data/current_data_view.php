<div class="container">
    <div class="row">
        <div class="col-md-12">
            <h2>Your Plantie </h2>
        </div>
    </div>


    <div class="row">
        <div class="col-xs-12 col-md-4">
            <div class="panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">Humidity</h3>
                </div>
                <div class="panel-body">
                    <h4><?= $humidity ?> %</h4>
                </div>
            </div>
        </div>
        <div class="col-xs-12 col-md-4">
            <div class="panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">Soil Humidity</h3>
                </div>
                <div class="panel-body">
                    <h4><?= $humidity_soil ?> %</h4>
                </div>
            </div>
        </div>
        <div class="col-xs-12 col-md-4">
            <div class="panel panel-default">
                <div class="panel-heading">
                    <h3 class="panel-title">Temperature</h3>
                </div>
                <div class="panel-body">
                    <h4><?= $temperature ?> °C</h4>
                </div>
            </div>
        </div>
    </div>
</div>