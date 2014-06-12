#ifndef JOINT_FEEDBACK_EX_MESSAGE_H
#define JOINT_FEEDBACK_EX_MESSAGE_H

#ifndef FLATHEADERS
#include "simple_message/typed_message.h"
#include "simple_message/simple_message.h"
#include "simple_message/shared_types.h"
#include "simple_message/joint_feedback.h"
#else
#include "typed_message.h"
#include "simple_message.h"
#include "shared_types.h"
#include "joint_feedback.h"
#endif

namespace industrial
{
namespace joint_feedback_ex_message
{


/**
 * \brief Class encapsulated joint feedback message generation methods
 * (either to or from a industrial::simple_message::SimpleMessage type.
 *
 * This message simply wraps the industrial::joint_feedback::JointFeedback data type.
 * The data portion of this typed message matches JointFeedback.
 *
 *
 * THIS CLASS IS NOT THREAD-SAFE
 *
 */

class JointFeedbackExMessage : public industrial::typed_message::TypedMessage

{
public:
  /**
   * \brief Default constructor
   *
   * This method creates an empty message.
   *
   */
  JointFeedbackExMessage(void);
  /**
   * \brief Destructor
   *
   */
  ~JointFeedbackExMessage(void);
  /**
   * \brief Initializes message from a simple message
   *
   * \param simple message to construct from
   *
   * \return true if message successfully initialized, otherwise false
   */
  bool init(industrial::simple_message::SimpleMessage & msg);

  /**
   * \brief Initializes message from a joint feedback structure
   *
   * \param joint feedback data structure
   *
   */
  void init(industrial::joint_feedback::JointFeedback & data);

  /**
   * \brief Initializes a new message
   *
   */
  void init();

  // Overrides - SimpleSerialize
  bool load(industrial::byte_array::ByteArray *buffer);
  bool unload(industrial::byte_array::ByteArray *buffer);

  unsigned int byteLength()
  {
    return this->data_.byteLength();
  }

  industrial::shared_types::shared_int getRobotID()
  {
    return this->data_.getRobotID();
  }

  bool getTime(industrial::shared_types::shared_real & time)
  {
    return this->data_.getTime(time);
  }

  bool getPositions(industrial::joint_data::JointData &dest)
  {
    return this->data_.getPositions(dest);
  }

  bool getVelocities(industrial::joint_data::JointData &dest)
  {
    return this->data_.getVelocities(dest);
  }

  bool getAccelerations(industrial::joint_data::JointData &dest)
  {
    return this->data_.getAccelerations(dest);
  }

private:

  industrial::joint_feedback::JointFeedback data_;

};

}
}


#endif // JOINT_FEEDBACK_EX_MESSAGE_H
