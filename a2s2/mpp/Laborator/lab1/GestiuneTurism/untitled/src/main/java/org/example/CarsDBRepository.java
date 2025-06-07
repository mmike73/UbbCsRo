package org.example;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Properties;

public class CarsDBRepository implements CarRepository{

    private JdbcUtils dbUtils;

    private static final Logger logger= LogManager.getLogger();

    public CarsDBRepository(Properties props) {
        logger.info("Initializing CarsDBRepository with properties: {} ",props);
        dbUtils=new JdbcUtils(props);
    }

    @Override
    public List<Car> findByManufacturer(String manufacturerN) {
        List<Car> cars = new ArrayList<>();
        String sql = "SELECT * FROM cars_pk";
        try (Connection conn = dbUtils.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                Car cet_car = new Car( rs.getString("manufacturer") , rs.getString("model") , rs.getInt("year"));
                if (cet_car.getManufacturer().equals(manufacturerN)) {
                    cars.add(cet_car);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return cars;
    }

    @Override
    public List<Car> findBetweenYears(int min, int max) {
        List<Car> cars = new ArrayList<>();
        String sql = "SELECT * FROM cars_pk";
        try (Connection conn = dbUtils.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                Car cet_car = new Car( rs.getString("manufacturer") , rs.getString("model") , rs.getInt("year"));
                if (min > cet_car.getYear() && cet_car.getYear() < max) {
                    cars.add(cet_car);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return cars;
    }

    @Override
    public void add(Car elem) {
        String sql = "INSERT INTO cars_pk (manufacturer, model, year) VALUES (?, ?, ?)";
        try (Connection conn = dbUtils.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, elem.getManufacturer());
            pstmt.setString(2, elem.getModel());
            pstmt.setInt(3, elem.getYear());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void update(Integer integer, Car elem) {
        String sql = "UPDATE cars_pk SET manufacturer=?, model=?, year=? WHERE id=?";
        try (Connection conn = dbUtils.getConnection();
             PreparedStatement pstmt = conn.prepareStatement(sql)) {
            pstmt.setString(1, elem.getManufacturer());
            pstmt.setString(2, elem.getModel());
            pstmt.setInt(3, elem.getYear());
            pstmt.setInt(4, elem.getId());
            pstmt.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    @Override
    public List<Car> findAll() {
        List<Car> cars = new ArrayList<>();
        String sql = "SELECT * FROM cars_pk";
        try (Connection conn = dbUtils.getConnection();
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {
            while (rs.next()) {
                cars.add(new Car( rs.getString("manufacturer") , rs.getString("model") , rs.getInt("year")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return cars;
    }
}
