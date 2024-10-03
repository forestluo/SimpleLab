////////////////////////////////////////////////////////////////////////////////
//
// Including Files
//
////////////////////////////////////////////////////////////////////////////////

#include <Global.h>
#include <SimpleSensor.h>

////////////////////////////////////////////////////////////////////////////////
//
// General Functions
//
////////////////////////////////////////////////////////////////////////////////

/**
 * Default deconstruction.
 *
 * @param None No parameters needed.
 * @return
 *     <p>No results returned.</p>
 */
SimpleSensor::~SimpleSensor(void)
{

}

/**
 * Default construction.
 *
 * @param id ID of sensor.
 * @return
 *     <p>No results returned.</p>
 */
SimpleSensor::SimpleSensor(_UINT16 id)
{
	//Set id.
	this->id = id;

#ifdef _DEBUG
	_PRINT2(">SimpleSensor::SimpleSensor: id(\"%c%c\") was initialized !",SID_MAJOR(id),SID_MINOR(id));
#endif

}

/**
 * Get id.
 *
 * @param None No parameters needed.
 * @return
 *     <p>ID of sensor.</p>
 */
_UINT16 SimpleSensor::getID(void)
{
	//Return id.
	return id;
}
