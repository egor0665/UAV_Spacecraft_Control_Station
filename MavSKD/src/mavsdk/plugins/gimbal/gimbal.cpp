// WARNING: THIS FILE IS AUTOGENERATED! As such, it should not be edited.
// Edits need to be made to the proto files
// (see https://github.com/mavlink/MAVSDK-Proto/blob/master/protos/gimbal/gimbal.proto)

#include <iomanip>

#include "gimbal_impl.h"
#include "plugins/gimbal/gimbal.h"

namespace mavsdk {

using ControlStatus = Gimbal::ControlStatus;

Gimbal::Gimbal(System& system) : PluginBase(), _impl{std::make_unique<GimbalImpl>(system)} {}

Gimbal::Gimbal(std::shared_ptr<System> system) :
    PluginBase(),
    _impl{std::make_unique<GimbalImpl>(system)}
{}

Gimbal::~Gimbal() {}

void Gimbal::set_pitch_and_yaw_async(float pitch_deg, float yaw_deg, const ResultCallback callback)
{
    _impl->set_pitch_and_yaw_async(pitch_deg, yaw_deg, callback);
}

Gimbal::Result Gimbal::set_pitch_and_yaw(float pitch_deg, float yaw_deg) const
{
    return _impl->set_pitch_and_yaw(pitch_deg, yaw_deg);
}

void Gimbal::set_pitch_rate_and_yaw_rate_async(
    float pitch_rate_deg_s, float yaw_rate_deg_s, const ResultCallback callback)
{
    _impl->set_pitch_rate_and_yaw_rate_async(pitch_rate_deg_s, yaw_rate_deg_s, callback);
}

Gimbal::Result
Gimbal::set_pitch_rate_and_yaw_rate(float pitch_rate_deg_s, float yaw_rate_deg_s) const
{
    return _impl->set_pitch_rate_and_yaw_rate(pitch_rate_deg_s, yaw_rate_deg_s);
}

void Gimbal::set_mode_async(GimbalMode gimbal_mode, const ResultCallback callback)
{
    _impl->set_mode_async(gimbal_mode, callback);
}

Gimbal::Result Gimbal::set_mode(GimbalMode gimbal_mode) const
{
    return _impl->set_mode(gimbal_mode);
}

void Gimbal::set_roi_location_async(
    double latitude_deg, double longitude_deg, float altitude_m, const ResultCallback callback)
{
    _impl->set_roi_location_async(latitude_deg, longitude_deg, altitude_m, callback);
}

Gimbal::Result
Gimbal::set_roi_location(double latitude_deg, double longitude_deg, float altitude_m) const
{
    return _impl->set_roi_location(latitude_deg, longitude_deg, altitude_m);
}

void Gimbal::take_control_async(ControlMode control_mode, const ResultCallback callback)
{
    _impl->take_control_async(control_mode, callback);
}

Gimbal::Result Gimbal::take_control(ControlMode control_mode) const
{
    return _impl->take_control(control_mode);
}

void Gimbal::release_control_async(const ResultCallback callback)
{
    _impl->release_control_async(callback);
}

Gimbal::Result Gimbal::release_control() const
{
    return _impl->release_control();
}

Gimbal::ControlHandle Gimbal::subscribe_control(const ControlCallback& callback)
{
    return _impl->subscribe_control(callback);
}

void Gimbal::unsubscribe_control(ControlHandle handle)
{
    _impl->unsubscribe_control(handle);
}

Gimbal::ControlStatus Gimbal::control() const
{
    return _impl->control();
}

bool operator==(const Gimbal::ControlStatus& lhs, const Gimbal::ControlStatus& rhs)
{
    return (rhs.control_mode == lhs.control_mode) &&
           (rhs.sysid_primary_control == lhs.sysid_primary_control) &&
           (rhs.compid_primary_control == lhs.compid_primary_control) &&
           (rhs.sysid_secondary_control == lhs.sysid_secondary_control) &&
           (rhs.compid_secondary_control == lhs.compid_secondary_control);
}

std::ostream& operator<<(std::ostream& str, Gimbal::ControlStatus const& control_status)
{
    str << std::setprecision(15);
    str << "control_status:" << '\n' << "{\n";
    str << "    control_mode: " << control_status.control_mode << '\n';
    str << "    sysid_primary_control: " << control_status.sysid_primary_control << '\n';
    str << "    compid_primary_control: " << control_status.compid_primary_control << '\n';
    str << "    sysid_secondary_control: " << control_status.sysid_secondary_control << '\n';
    str << "    compid_secondary_control: " << control_status.compid_secondary_control << '\n';
    str << '}';
    return str;
}

std::ostream& operator<<(std::ostream& str, Gimbal::Result const& result)
{
    switch (result) {
        case Gimbal::Result::Unknown:
            return str << "Unknown";
        case Gimbal::Result::Success:
            return str << "Success";
        case Gimbal::Result::Error:
            return str << "Error";
        case Gimbal::Result::Timeout:
            return str << "Timeout";
        case Gimbal::Result::Unsupported:
            return str << "Unsupported";
        case Gimbal::Result::NoSystem:
            return str << "No System";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, Gimbal::GimbalMode const& gimbal_mode)
{
    switch (gimbal_mode) {
        case Gimbal::GimbalMode::YawFollow:
            return str << "Yaw Follow";
        case Gimbal::GimbalMode::YawLock:
            return str << "Yaw Lock";
        default:
            return str << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& str, Gimbal::ControlMode const& control_mode)
{
    switch (control_mode) {
        case Gimbal::ControlMode::None:
            return str << "None";
        case Gimbal::ControlMode::Primary:
            return str << "Primary";
        case Gimbal::ControlMode::Secondary:
            return str << "Secondary";
        default:
            return str << "Unknown";
    }
}

} // namespace mavsdk