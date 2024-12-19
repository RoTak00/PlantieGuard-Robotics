<?php

class DataDataModel extends BaseModel
{
    public function getDeviceData($limit = 0, $offset = 0)
    {

        $sql = "SELECT * FROM pg_data pd 
        LEFT JOIN users u ON pd.token = u.token
        WHERE u.id = " . (int) $this->user->getId() . " 
        ORDER BY date_added DESC";

        if ($limit > 0) {
            $sql .= " LIMIT " . (int) $limit;

            if ($offset > 0) {
                $sql .= " OFFSET " . (int) $offset;
            }
        }


        $result = $this->db->query($sql);


        return $result->fetch_all(MYSQLI_ASSOC);
    }

    public function getMostRecentDataEntry()
    {
        $result = $this->getDeviceData(1, 0);

        if (!empty($result)) {
            return $result[0];
        }

        return [];
    }



}