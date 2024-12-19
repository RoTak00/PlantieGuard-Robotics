<?php

class AccountUserModel extends BaseModel
{


    public function get_user_by_username($name)
    {
        $sql = "SELECT * FROM users WHERE name = '" . $this->db->escape($name) . "'";

        $result = $this->db->query($sql);

        if ($result->num_rows > 0) {
            return true;
        } else {
            return false;
        }
    }

    // get user by email

    public function get_user_by_email($email)
    {
        $sql = "SELECT * FROM users WHERE email = '" . $this->db->escape($email) . "'";

        $result = $this->db->query($sql);

        if ($result->num_rows > 0) {
            return true;
        } else {
            return false;
        }
    }
}