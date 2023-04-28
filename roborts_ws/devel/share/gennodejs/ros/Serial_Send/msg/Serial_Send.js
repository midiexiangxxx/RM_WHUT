// Auto-generated. Do not edit!

// (in-package Serial_Send.msg)


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
      this.gimbal_x = null;
      this.gimbal_y = null;
      this.gimbal_z = null;
      this.vx_set = null;
      this.vy_set = null;
      this.wz_set = null;
    }
    else {
      if (initObj.hasOwnProperty('gimbal_x')) {
        this.gimbal_x = initObj.gimbal_x
      }
      else {
        this.gimbal_x = 0.0;
      }
      if (initObj.hasOwnProperty('gimbal_y')) {
        this.gimbal_y = initObj.gimbal_y
      }
      else {
        this.gimbal_y = 0.0;
      }
      if (initObj.hasOwnProperty('gimbal_z')) {
        this.gimbal_z = initObj.gimbal_z
      }
      else {
        this.gimbal_z = 0.0;
      }
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
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type Serial_Send
    // Serialize message field [gimbal_x]
    bufferOffset = _serializer.float32(obj.gimbal_x, buffer, bufferOffset);
    // Serialize message field [gimbal_y]
    bufferOffset = _serializer.float32(obj.gimbal_y, buffer, bufferOffset);
    // Serialize message field [gimbal_z]
    bufferOffset = _serializer.float32(obj.gimbal_z, buffer, bufferOffset);
    // Serialize message field [vx_set]
    bufferOffset = _serializer.float32(obj.vx_set, buffer, bufferOffset);
    // Serialize message field [vy_set]
    bufferOffset = _serializer.float32(obj.vy_set, buffer, bufferOffset);
    // Serialize message field [wz_set]
    bufferOffset = _serializer.float32(obj.wz_set, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Serial_Send
    let len;
    let data = new Serial_Send(null);
    // Deserialize message field [gimbal_x]
    data.gimbal_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [gimbal_y]
    data.gimbal_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [gimbal_z]
    data.gimbal_z = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vx_set]
    data.vx_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy_set]
    data.vy_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [wz_set]
    data.wz_set = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'Serial_Send/Serial_Send';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '33a15562caea82466375017bafdca201';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 gimbal_x
    float32 gimbal_y
    float32 gimbal_z
    float32 vx_set
    float32 vy_set
    float32 wz_set
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Serial_Send(null);
    if (msg.gimbal_x !== undefined) {
      resolved.gimbal_x = msg.gimbal_x;
    }
    else {
      resolved.gimbal_x = 0.0
    }

    if (msg.gimbal_y !== undefined) {
      resolved.gimbal_y = msg.gimbal_y;
    }
    else {
      resolved.gimbal_y = 0.0
    }

    if (msg.gimbal_z !== undefined) {
      resolved.gimbal_z = msg.gimbal_z;
    }
    else {
      resolved.gimbal_z = 0.0
    }

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

    return resolved;
    }
};

module.exports = Serial_Send;
