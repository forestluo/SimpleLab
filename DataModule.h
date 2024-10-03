#ifndef _DATA_MODULE_H
#define _DATA_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files
//
////////////////////////////////////////////////////////////////////////////////

#include <SPIChip.h>
#include <ChipADS1247.h>

////////////////////////////////////////////////////////////////////////////////
//
// Data Module
//
////////////////////////////////////////////////////////////////////////////////

class DataModule
{
private:
	/**
     * Chip ADS1247.
	 */
	ChipADS1247 chipADS1247;

private:
	/**
     * Pin value.
	 */
	_INT32 pinValue;
	/**
	 * Sample rate.
	 */
	_SHORT sampleRate;
	/**
	 * Sample timestamp.
	 *
	 * <p>It is for internal using.</p>
	 */
	_UINT32 sampleTimestamp;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~DataModule(void);

	/**
	 * Default construction.
	 *
	 * @param chipADS1247SelectPin Pin for selecting ADS1247 chip.
	 * @return
	 *     <p>No results returned.</p>
	 */
	DataModule(DigitalPin chipADS1247SelectPin);

public:
	/**
     * Read registers.
	 *
	 * @param None No parameters needed.
	 * @return
	 *    <p>Value of registers.</p>
	 */
	_UINT64 readRegisters();

	/**
	 * Write registers.
	 *
	 * @param value Value of registers.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeRegisters(_UINT64 value);

public:
	/**
     * Whether sample is timeout.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if sample is timeout.</p>
	 */
	_BOOL isSampleTimeout(void);

	/**
	 * Get sample rate.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Sample rate.</p>
	 */
	_SHORT getSampleRate(void);

	/**
     * Set sample rate.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void setSampleRate(_SHORT sampleRate);

public:
	/**
     * Get pin value.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Pin value.</p>
	 */
	_INT32 getPinValue(void);

	/**
     * Read AVDD.
	 *
	 * @param keepRegisters Whether keep registers.
	 * @return
	 *     <p>AVDD of chip.</p>
	 */
	_FLOAT readAVDD(_BOOL keepRegisters);

	/**
     * Read sample value.
	 *
	 * @param value Sample value.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void readSampleValue(SampleValue& value);

public:
	/**
	 * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);

};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !