// Auto-generated. Do not edit!

// (in-package serial_send.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class Serial_Send {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vx_set = null;
      this.vy_set = null;
      this.wz_set = null;
      this.yaw_add = null;
      this.pitch_add = null;
      this.mode = null;
    }
    else {
      if (initObj.hasOwnProperty('vx_set')) {
        this.vx_set = initObj.vx_set
      }
      else {
        this.vx_set = 0.0;
      }
      if (initObj.hasOwnProperty('vy_set')) {
        this.vy_set = initObj.vy_set
      }
      else {
        this.vy_set = 0.0;
      }
      if (initObj.hasOwnProperty('wz_set')) {
        this.wz_set = initObj.wz_set
      }
      else {
        this.wz_set = 0.0;
      }
      if (initObj.hasOwnProperty('yaw_add')) {
        this.yaw_add = initObj.yaw_add
      }
      else {
        this.yaw_add = 0.0;
      }
      if (initObj.hasOwnProperty('pitch_add')) {
        this.pitch_add = initObj.pitch_add
      }
      else {
        this.pitch_add = 0.0;
      }
      if (initObj.hasOwnProperty('mode')) {
        this.mode = initObj.mode
      }
      else {
        this.mode = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Serial_Send
    // Serialize message field [vx_set]
    bufferOffset = _serializer.float32(obj.vx_set, buffer, bufferOffset);
    // Serialize message field [vy_set]
    bufferOffset = _serializer.float32(obj.vy_set, buffer, bufferOffset);
    // Serialize message field [wz_set]
    bufferOffset = _serializer.float32(obj.wz_set, buffer, bufferOffset);
    // Serialize message field [yaw_add]
    bufferOffset = _serializer.float32(obj.yaw_add, buffer, bufferOffset);
    // Serialize message field [pitch_add]
    bufferOffset = _serializer.float32(obj.pitch_add, buffer, bufferOffset);
    // Serialize message field [mode]
    bufferOffset = _serializer.uint8(obj.mode, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Serial_Send
    let len;
    let data = new Serial_Send(null);
    // Deserialize message field [vx_set]
    data.vx_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy_set]
    data.vy_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wz_set]
    data.wz_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw_add]
    data.yaw_add = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pitch_add]
    data.pitch_add = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [mode]
    data.mode = _deserializer.uint8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 21;
  }

  static datatype() {
    // Returns string type for a message object
    return 'serial_send/Serial_Send';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '73de9545dab8a1f88fa0fdc921aa3bba';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 vx_set
    float32 vy_set
    float32 wz_set
    float32 yaw_add
    float32 pitch_add
    uint8 mode
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Serial_Send(null);
    if (msg.vx_set !== undefined) {
      resolved.vx_set = msg.vx_set;
    }
    else {
      resolved.vx_set = 0.0
    }

    if (msg.vy_set !== undefined) {
      resolved.vy_set = msg.vy_set;
    }
    else {
      resolved.vy_set = 0.0
    }

    if (msg.wz_set !== undefined) {
      resolved.wz_set = msg.wz_set;
    }
    else {
      resolved.wz_set = 0.0
    }

    if (msg.yaw_add !== undefined) {
      resolved.yaw_add = msg.yaw_add;
    }
    else {
      resolved.yaw_add = 0.0
    }

    if (msg.pitch_add !== undefined) {
      resolved.pitch_add = msg.pitch_add;
    }
    else {
      resolved.pitch_add = 0.0
    }

    if (msg.mode !== undefined) {
      resolved.mode = msg.mode;
    }
    else {
      resolved.mode = 0
    }

    return resolved;
    }
};

module.exports = Serial_Send;
