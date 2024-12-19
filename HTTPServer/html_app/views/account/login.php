<?= $head ?>
<?= $navigation ?>


<div class="container">
    <form method="POST">
        <div class="row">
            <div class="col-xs-12 col-md-6">
                <div class="form-group">
                    <label for="email">Email

                        <?php if (isset($error['email'])) { ?>
                            <span class="text-danger">&nbsp;<?= $error['email'] ?></span>
                        <?php } ?></label>
                    <input type="email" class="form-control" id="email" name="email" value="<?= $email ?>"
                        placeholder="Email" required>

                </div>



            </div>
            <div class="col-xs-12 col-md-6">
                <div class="form-group">
                    <label for="password">Password

                        <?php if (isset($error['password'])) { ?>
                            <span class="text-danger">&nbsp;<?= $error['password'] ?></span>
                        <?php } ?></label>
                    <input type="password" class="form-control" id="password" name="password" placeholder="Password"
                        required>

                </div>
            </div>
        </div>

        <div class="row">
            <div class="col-xs-12">
                <div class="form-group">
                    <button type="submit" class="btn btn-primary d-block mx-auto mt-4 w-25">Login</button>
                </div>
            </div>
        </div>

    </form>
</div>
<?= $footer ?>