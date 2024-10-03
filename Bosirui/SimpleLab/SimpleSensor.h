#ifndef _SIMPLE_SENSOR_H
#define _SIMPLE_SENSOR_H

////////////////////////////////////////////////////////////////////////////////
//
// General definitions
//
////////////////////////////////////////////////////////////////////////////////

#define SENSOR_A1											0x4131
#define SENSOR_A2											0x4132
#define SENSOR_B1											0x4231
#define SENSOR_B2											0x4232
#define SENSOR_C1											0x4331
#define SENSOR_C2											0x4332
#define SENSOR_D1											0x4431
#define SENSOR_D2											0x4432
#define SENSOR_E1											0x4531
#define SENSOR_E2											0x4532
#define SENSOR_E3											0x4533
#define SENSOR_E4											0x4534
#define SENSOR_F1											0x4631
#define SENSOR_F2											0x4632
#define SENSOR_F3											0x4633
#define SENSOR_F4											0x4634
#define SENSOR_G1											0x4731
#define SENSOR_G2											0x4732
#define SENSOR_G3											0x4733
#define SENSOR_G4											0x4734
#define SENSOR_H1											0x4831
#define SENSOR_H2											0x4832
#define SENSOR_H3											0x4833
#define SENSOR_K1											0x4B31
#define SENSOR_K2											0x4B32
#define SENSOR_K3											0x4B33
#define SENSOR_L1											0x4C31
#define SENSOR_L2											0x4C32
#define SENSOR_L3											0x4C33
#define SENSOR_M1											0x4D31
#define SENSOR_N1											0x4E31
#define SENSOR_X1											0x5831

////////////////////////////////////////////////////////////////////////////////
//
// Simple Sensor
//
////////////////////////////////////////////////////////////////////////////////

class SimpleSensor
{
private:
	/**
	 * ID of sensor.
	 */
	_UINT16 id;

public:
	/**
     * Default construction.
	 *
	 * @param id ID of sensor.
	 * @return
	 *     <p>No results returned.</p>
	 */
	SimpleSensor(_UINT16 id);
	
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~SimpleSensor(void);

public:
	/**
	 * Get id.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>ID of sensor.</p>
	 */
	_UINT16 getID(void);
};

////////////////////////////////////////////////////////////////////////////////
//
// General functions
//
////////////////////////////////////////////////////////////////////////////////

#define SID_MAJOR(v) \
	((char)((v) >> 8))
#define SID_MINOR(v) \
	((char)((v) & 0xFF))
#define SID(major,minor) \
	((_UINT16)((((major) & 0xFF) << 8) | ((minor) & 0xFF)))

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !