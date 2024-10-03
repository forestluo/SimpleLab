#ifndef _REAL_DEVICE_H
#define _REAL_DEVICE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <SampleTable.h>

#include <DataModule.h>
#include <ConfigModule.h>
#include <RecorderModule.h>

////////////////////////////////////////////////////////////////////////////////
//
// Real Device
//
////////////////////////////////////////////////////////////////////////////////

class RealDevice
{
protected:
	/**
     * Device type.
	 */
	_UINT32 deviceType;

	/**
	 * Sequence id.
	 *
	 * <p>It is used in cycle.</p>
	 */
	_UINT16 sequenceID;
	/**
	 * Sample value.
	 */
	_FLOAT sampleValue;
	/**
	 * Average value.
	 */
	_FLOAT averageValue;
	/**
	 * ADS1247 mode.
	 */
	_UINT64 ads1247Mode;
	/**
	 * Sample table.
	 */
	SampleTable sampleTable;

public:
	/**
	 * Default construction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	RealDevice(void);

private:
	/**
	 * Whether is valid mode.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if mode is valid.</p>
	 */
	_BOOL isValidMode(void) const;

	/**
	 * Whether ads1247 is needed.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if device type is needed.</p>
	 */
	_BOOL isADS1247Needed(void) const;

public:
	/**
     * Invalidate.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void invalidate(void);

	/**
     * Get type.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Type of device.</p>
	 */
	_UINT32 getType(void) const;

	/**
     * Get mode.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mode of ADS1247.</p>
	 */
	_UINT64 getMode(void) const;

public:
	/**
     * Get min index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Mininum index of table.</p>
	 */
	_INT32 getMinIndex(void);

	/**
     * Get max index.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Maxinum index of table.</p>
	 */
	_INT32 getMaxIndex(void);

	/**
     * Get sample value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Sample value.</p>
	 */
	_FLOAT getSampleValue(void) const;

	/**
     * Get average value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Average value.</p>
	 */
	_FLOAT getAverageValue(void) const;

public:
	/**
	 * Load config.
	 *
	 * @param configModule Config module.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL loadConfig(ConfigModule& configModule);

	/**
	 * Activate data module.
	 *
	 * @param dataModule Data module.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void activateDataModule(DataModule& dataModule);

	/**
     * Read data module.
	 *
	 * @param dataModule Data module.
	 * @param value Sample value.
	 * @return
	 *     <p>Return true,if there is a valid sample.</p>
	 */
	_BOOL readDataModule(DataModule& dataModule,SampleValue& value);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !