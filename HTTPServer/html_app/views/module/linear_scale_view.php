<?php if (!empty($title)) { ?>
    <h3 class="linear-view-title"><?= $title ?></h3>
<?php } ?>

<div class="linear-view-container">
    <div class="linear-view-bar" style="width: <?= $percentage ?>%; background-color: <?= $color ?>">

    </div>
    <p class="linear-view-value"><?= $value ?><?= $symbol ?></p>
</div>