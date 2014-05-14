#ifndef FLATHEADERS
#include "simple_message/joint_traj_pt_data.h"
#include "simple_message/shared_types.h"
#include "simple_message/log_wrapper.h"
#else
#include "joint_traj_pt_data.h"
#include "shared_types.h"
#include "log_wrapper.h"
#endif

using namespace industrial::joint_data;
using namespace industrial::shared_types;

namespace industrial
{
namespace joint_traj_pt_data
{

JointTrajPtData::JointTrajPtData(void)
{
  this->init();
}
JointTrajPtData::~JointTrajPtData(void)
{

}

void JointTrajPtData::init()
{
  this->group_number_ = 0;
  this->valid_fields_ = 0;
  this->time_ = 0.0;
  this->positions_.init();
  this->velocities_.init();
  this->accelerations_.init();
}

void JointTrajPtData::init(industrial::shared_types::shared_int group_number,
          industrial::shared_types::shared_int valid_fields,
          industrial::shared_types::shared_real time,
          industrial::joint_data::JointData & positions,
          industrial::joint_data::JointData & velocities,
          industrial::joint_data::JointData & accelerations)
{
  this->setGroupNumber(group_number);
  this->setTime(time);
  this->setPositions(positions);
  this->setVelocities(velocities);
  this->setAccelerations(accelerations);
  this->valid_fields_ = valid_fields;  // must happen after others are set
}

void JointTrajPtData::copyFrom(JointTrajPtData &src)
{
  this->setGroupNumber(src.getGroupNumber());
  src.getTime(this->time_);
  src.getPositions(this->positions_);
  src.getVelocities(this->velocities_);
  src.getAccelerations(this->accelerations_);
  this->valid_fields_ = src.valid_fields_;
}

bool JointTrajPtData::operator==(JointTrajPtData &rhs)
{
  return this->group_number_ == rhs.group_number_ &&
         this->valid_fields_ == rhs.valid_fields_ &&
         ( !is_valid(ValidFieldTypes::TIME) || (this->time_ == rhs.time_) ) &&
         ( !is_valid(ValidFieldTypes::POSITION) || (this->positions_ == rhs.positions_) ) &&
         ( !is_valid(ValidFieldTypes::VELOCITY) || (this->velocities_ == rhs.velocities_) ) &&
         ( !is_valid(ValidFieldTypes::ACCELERATION) || (this->accelerations_ == rhs.accelerations_) );
}

bool JointTrajPtData::load(industrial::byte_array::ByteArray *buffer)
{
  LOG_COMM("Executing joint trajectory point load");

  if (!buffer->load(this->group_number_))
  {
    LOG_ERROR("Failed to load joint traj pt. group_number");
    return false;
  }


  if (!buffer->load(this->valid_fields_))
  {
    LOG_ERROR("Failed to load joint traj. pt. valid fields");
    return false;
  }

  if (!buffer->load(this->time_))
  {
    LOG_ERROR("Failed to load joint traj. pt. time");
    return false;
  }

  if (!this->positions_.load(buffer))
  {
    LOG_ERROR("Failed to load joint traj. pt. positions");
    return false;
  }

  if (!this->velocities_.load(buffer))
  {
    LOG_ERROR("Failed to load joint traj. pt. velocities");
    return false;
  }

  if (!this->accelerations_.load(buffer))
  {
    LOG_ERROR("Failed to load joint traj. pt. accelerations");
    return false;
  }

  LOG_COMM("Trajectory point successfully loaded");
  return true;
}

bool JointTrajPtData::unload(industrial::byte_array::ByteArray *buffer)
{
  LOG_COMM("Executing joint traj. pt. unload");

  if (!this->accelerations_.unload(buffer))
  {
    LOG_ERROR("Failed to unload joint traj. pt. accelerations");
    return false;
  }

  if (!this->velocities_.unload(buffer))
  {
    LOG_ERROR("Failed to unload joint traj. pt. velocities");
    return false;
  }

  if (!this->positions_.unload(buffer))
  {
    LOG_ERROR("Failed to unload joint traj. pt. positions");
    return false;
  }

  if (!buffer->unload(this->time_))
  {
    LOG_ERROR("Failed to unload joint traj. pt. time");
    return false;
  }

  if (!buffer->unload(this->valid_fields_))
  {
    LOG_ERROR("Failed to unload joint traj. pt. valid fields");
    return false;
  }


  if (!buffer->unload(this->group_number_))
  {
    LOG_ERROR("Faild to unload joint traj. pt. group_number");
    return false;
  }

  LOG_COMM("Joint traj. pt successfully unloaded");
  return true;
}

}
}


