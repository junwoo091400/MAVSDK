//
// Example how to run the sensor calibrations.
//
// Best tested against a real flight controller like a Pixhawk
// and not against simulation.
//

#include <mavsdk/mavsdk.h>
#include <mavsdk/plugins/calibration/calibration.h>
#include <future>
#include <iostream>

using namespace mavsdk;
using std::chrono::seconds;

static std::function<void(Calibration::Result, Calibration::ProgressData)>
create_calibration_callback(std::promise<void>&);

static void calibrate_accelerometer(Calibration&);
static void calibrate_gyro(Calibration&);
static void calibrate_magnetometer(Calibration&);

void usage(const std::string& bin_name)
{
    std::cerr << "Usage : " << bin_name << " <connection_url>\n"
              << "Connection URL format should be :\n"
              << " For TCP : tcp://[server_host][:server_port]\n"
              << " For UDP : udp://[bind_host][:bind_port]\n"
              << " For Serial : serial:///path/to/serial/dev[:baudrate]\n"
              << "For example, to connect to the simulator use URL: udp://:14540\n";
}

std::shared_ptr<System> get_system(Mavsdk& mavsdk)
{
    std::cout << "Waiting to discover system...\n";
    auto prom = std::promise<std::shared_ptr<System>>{};
    auto fut = prom.get_future();

    // We wait for new systems to be discovered, once we find one that has an
    // autopilot, we decide to use it.
    Mavsdk::NewSystemHandle handle = mavsdk.subscribe_on_new_system([&mavsdk, &prom, &handle]() {
        auto system = mavsdk.systems().back();

        if (system->has_autopilot()) {
            std::cout << "Discovered autopilot\n";

            // Unsubscribe again as we only want to find one system.
            mavsdk.unsubscribe_on_new_system(handle);
            prom.set_value(system);
        }
    });

    // We usually receive heartbeats at 1Hz, therefore we should find a
    // system after around 3 seconds max, surely.
    if (fut.wait_for(seconds(3)) == std::future_status::timeout) {
        std::cerr << "No autopilot found.\n";
        return {};
    }

    // Get discovered system now.
    return fut.get();
}

int main(int argc, char** argv)
{
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }

    Mavsdk mavsdk;
    ConnectionResult connection_result = mavsdk.add_any_connection(argv[1]);

    if (connection_result != ConnectionResult::Success) {
        std::cerr << "Connection failed: " << connection_result << '\n';
        return 1;
    }

    auto system = get_system(mavsdk);
    if (!system) {
        return 1;
    }

    // Instantiate plugin.
    auto calibration = Calibration(system);

    // Run calibrations
    calibrate_accelerometer(calibration);
    calibrate_gyro(calibration);
    calibrate_magnetometer(calibration);

    return 0;
}

void calibrate_accelerometer(Calibration& calibration)
{
    std::cout << "Calibrating accelerometer...\n";

    std::promise<void> calibration_promise;
    auto calibration_future = calibration_promise.get_future();

    calibration.calibrate_accelerometer_async(create_calibration_callback(calibration_promise));

    calibration_future.wait();
}

std::function<void(Calibration::Result, Calibration::ProgressData)>
create_calibration_callback(std::promise<void>& calibration_promise)
{
    return [&calibration_promise](
               const Calibration::Result result, const Calibration::ProgressData progress_data) {
        switch (result) {
            case Calibration::Result::Success:
                std::cout << "--- Calibration succeeded!\n";
                calibration_promise.set_value();
                break;
            case Calibration::Result::Next:
                if (progress_data.has_progress) {
                    std::cout << "    Progress: " << progress_data.progress << '\n';
                }
                if (progress_data.has_status_text) {
                    std::cout << "    Instruction: " << progress_data.status_text << '\n';
                }
                break;
            default:
                std::cout << "--- Calibration failed with message: " << result << '\n';
                calibration_promise.set_value();
                break;
        }
    };
}

void calibrate_gyro(Calibration& calibration)
{
    std::cout << "Calibrating gyro...\n";

    std::promise<void> calibration_promise;
    auto calibration_future = calibration_promise.get_future();

    calibration.calibrate_gyro_async(create_calibration_callback(calibration_promise));

    calibration_future.wait();
}

void calibrate_magnetometer(Calibration& calibration)
{
    std::cout << "Calibrating magnetometer...\n";

    std::promise<void> calibration_promise;
    auto calibration_future = calibration_promise.get_future();

    calibration.calibrate_magnetometer_async(create_calibration_callback(calibration_promise));

    calibration_future.wait();
}
