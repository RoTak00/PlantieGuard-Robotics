<?php

class AccountUuidModel extends BaseModel
{
    public function check_uuid($uuid)
    {
        $sql = "SELECT * FROM pg_devices WHERE token = '" . $this->db->escape($uuid) . "'";

        $result = $this->db->query($sql);

        if ($result->num_rows > 0) {
            return true;
        } else {
            return false;
        }
    }


    public function get_user_by_uuid($uuid)
    {
        $sql = "SELECT * FROM users WHERE token = '" . $this->db->escape($uuid) . "'";

        $result = $this->db->query($sql);

        if ($result->num_rows > 0) {
            return true;
        } else {
            return false;
        }
    }

    public function set_uuid($uuid)
    {
        $sql = "UPDATE users SET token = '" . $this->db->escape($uuid) . "' WHERE id = " . (int) $this->user->getId();

        $result = $this->db->query($sql);
    }
}