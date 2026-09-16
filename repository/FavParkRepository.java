package edu.usc.csci310.project.repository;


import edu.usc.csci310.project.model.FavPark;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
public interface FavParkRepository extends JpaRepository<FavPark, Long> {
    Optional<FavPark> findByParkIdAndUsrId(String parkId, Long usrId);

    boolean existsByParkIdAndUsrId(String parkId, Long usrId);

    List<FavPark> findByUsrId(Long usrId);
}