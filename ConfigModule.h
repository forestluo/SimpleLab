#ifndef _CONFIG_MODULE_H
#define _CONFIG_MODULE_H

////////////////////////////////////////////////////////////////////////////////
//
// Including files.
//
////////////////////////////////////////////////////////////////////////////////

#include <SampleTable.h>

#include <I2CChip.h>
#include <ChipAT24C128N.h>

////////////////////////////////////////////////////////////////////////////////
//
// Config Module
//
////////////////////////////////////////////////////////////////////////////////

class ConfigModule
{
private:
	/**
	 * Chip AT24C128N.
	 */
	ChipAT24C128N chipAT24C128N;

private:
	/**
     * Flags.
	 */
	_BYTE flags;

public:
	/**
     * Default deconstruction.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	virtual ~ConfigModule(void);

	/**
	 * Default construction.
	 *
	 * @param chipAT24C128NAddress Address for chip AT24C128N.
	 * @return
	 *     <p>No results returned.</p>
	 */
	ConfigModule(_UINT8 chipAT24C128NAddress);

public:
	/**
     * Read uint8.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT8 readUint8(_UINT16 dataAddress);

	/**
     * Read uint16.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT16 readUint16(_UINT16 dataAddress);

	/**
     * Read uint32.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT32 readUint32(_UINT16 dataAddress);

	/**
     * Read uint64.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Value of data.</p>
	 */
	_UINT64 readUint64(_UINT16 dataAddress);

public:
	/**
	 * Write uint8.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeUint8(_UINT16 dataAddress,_UINT8 value);

	/**
	 * Write uint16.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeUint16(_UINT16 dataAddress,_UINT16 value);

	/**
	 * Write uint32.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeUint32(_UINT16 dataAddress,_UINT32 value);

	/**
	 * Write uint64.
	 *
	 * @param dataAddress Address of data.
	 * @param value Value of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeUint64(_UINT16 dataAddress,_UINT64 value);

private:
	/**
	 * Read null id.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL readNullID(_UINT16 dataAddress);

	/**
	 * Read magic number.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Magic number.</p>
	 */
	_UINT32 readMagicNumber(_UINT16 dataAddress);

	/**
	 * Read version.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Version.</p>
	 */
	_UINT16 readVersion(_UINT16 dataAddress);

	/**
	 * Read counter.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Counter.</p>
	 */
	_UINT32 readCounter(_UINT16 dataAddress);

	/**
	 * Read device type.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Device type.</p>
	 */
	_UINT32 readDeviceType(_UINT16 dataAddress);

	/**
	 * Read ads1247 mode.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>ADS1247 mode.</p>
	 */
	_UINT64 readADS1247Mode(_UINT16 dataAddress);

	/**
	 * Read sample table.
	 *
	 * @param dataAddress Address of data.
	 * @param table sample table.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL readSampleTable(_UINT16 dataAddress,SampleTable& table);

private:
	/**
	 * Write null id.
	 *
	 * @param dataAddress Address of data.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeNullID(_UINT16 dataAddress);

	/**
	 * Write magic number.
	 *
	 * @param dataAddress Address of data.
	 * @param magicNumber Magic number.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeMagicNumber(_UINT16 dataAddress,_UINT32 magicNumber);

	/**
	 * Write version.
	 *
	 * @param dataAddress Address of data.
	 * @param version Version.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeVersion(_UINT16 dataAddress,_UINT16 version);

	/**
	 * Write counter.
	 *
	 * @param dataAddress Address of data.
	 * @param counter Counter.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeCounter(_UINT16 dataAddress,_UINT32 counter);

	/**
	 * Write device type.
	 *
	 * @param dataAddress Address of data.
	 * @param deviceType Device type.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeDeviceType(_UINT16 dataAddress,_UINT32 deviceType);

	/**
	 * Write ADS1247 mode.
	 *
	 * @param dataAddress Address of data.
	 * @param ads1247Mode ADS1247 mode.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeADS1247Mode(_UINT16 dataAddress,_UINT64 ads1247Mode);

	/**
	 * Write sample table.
	 *
	 * @param dataAddress Address of data.
	 * @param table Sample table.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL writeSampleTable(_UINT16 dataAddress,SampleTable& table);

private:
	/**
     * Read magic number.
	 *
	 * <p>Read magic number from internal E2PROM.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Magic number.</p>
	 */
	_UINT32 readMagicNumber(void);

	/**
     * Read magic number.
	 *
	 * <p>Read counter from internal E2PROM.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Counter.</p>
	 */
	_UINT32 readCounter(void);

private:
	/**
     * Write magic number.
	 *
	 * <p>Write magic number into internal E2PROM.</p>
	 *
	 * @param magicNumber Magic number.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeMagicNumber(_UINT32 magicNumber);

	/**
     * Write counter.
	 *
	 * <p>Write counter into internal E2PROM.</p>
	 *
	 * @param counter Counter.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeCounter(_UINT32 counter);

public:
	/**
     * Read MAC address.
	 *
	 * <p>Read MAC address from internal E2PROM.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>MAC address.</p>
	 */
	_UINT64 readMACAddress(void);

	/**
     * Write MAC address.
	 *
	 * <p>Write MAC address into internal E2PROM.</p>
	 *
	 * @param macAddress MAC address.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void writeMACAddress(_UINT64 macAddress);

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
     * Whether available.
	 *
	 * <p>It depends on flags.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if config is available.</p>
	 */
	_BOOL isAvailable(void);

	/**
	 * Check version.
	 *
	 * @param version Version.
	 * @return
	 *     <p>Return true, if device exists.</p>
	 */
	_BOOL checkVersion(_UINT16 version);

public:
	/**
     * Dump config.
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>No results returned.</p>
	 */
	void dumpConfig(void);

	/**
     * Format config.
	 *
	 * <p>Use default config to format.</p>
	 *
	 * @param None No parameters needed.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL formatConfig(void);

	/**
     * Load config.
	 *
	 * @param deviceType Type of device.
	 * @param ads1247Mode Mode of ADS1247.
	 * @param sampleTable Sample table.
	 * @return
	 *     <p>Return true, if successfully done.</p>
	 */
	_BOOL loadConfig(_UINT32& deviceType,_UINT64& ads1247Mode,SampleTable& sampleTable);
};

////////////////////////////////////////////////////////////////////////////////

#endif //End of the head file !