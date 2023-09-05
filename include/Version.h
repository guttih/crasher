
#ifndef VERSION_H
#define VERSION_H

#define MAX_UINT_STRING_LEN 20
#define MAX_VERSION_STRING_LEN ( 4 * MAX_UINT_STRING_LEN ) + 3 + 1

enum VERSION
{
    MAJOR = 0,
    MINOR,
    PATCH,
    BUILD
};

class Version
{
private:
    unsigned int _version[ 4 ] = { 0, 0, 0, 0 };
    char *m_versionString = nullptr;
    const char *itoa( unsigned int val, int base );

public:
    // operators
    Version &operator=( const Version &rhs );
    Version &operator++();                  // Prefix increment operator.
    Version operator++( int incrementBuild ); // Postfix increment operator.
    Version &operator+=( const int &incrementBuild );
    Version operator+( const int &incrementBuild );
    bool operator==( const Version &rhs );
    bool operator>( const Version &rhs );
    bool operator<( const Version &rhs );
    bool operator!=( const Version &rhs );
    bool operator>=( const Version &rhs );
    bool operator<=( const Version &rhs );

    /**
     * @brief Returns the version as a string.  Note after you change any of the
     *        version numbers this function must be called to update the string.
     *
     * @param showLastZeroPos Do not print trailing zeros after this significance.
     *                          For example, if version is 3.0.0.0 then
     *                          VERSION::BUILD will return "3.0.0.0"
     *                          VERSION::PATCH will return "3.0.0"
     *                          VERSION::MINOR will return "3.0"
     *                          VERSION::MAJOR will return "3"
     * @return const char*
     */
    const char *c_str( VERSION showLastZeroPos = VERSION::MINOR );
    Version( unsigned int major, unsigned int minor, unsigned int patch = 0, unsigned int build = 0 );
    Version( const char *version = nullptr );
    void set( const char *value );
    void set( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build );
    /**
     * @brief Set the Major version number and minor- patch- and build numbers to zero
     *
     * @param major
     */
    void setMajor( unsigned int major );
    /**
     * @brief Set the Minor version number and patch and build numbers to zero
     *
     * @param minor
     */
    void setMinor( unsigned int minor );
    /**
     * @brief Set the Patch version number and build number to zero
     *
     * @param patch
     */
    void setPatch( unsigned int patch );
    /**
     * @brief Set the Build version number
     *
     * @param patch
     */
    void setBuild( unsigned int build );

    /**
     * @brief Increment the Major version number set and minor, patch and build number to zero
     *
     */
    void IncrementMajor();

    /**
     * @brief Increment the Minor version number set and patch and build number to zero
     *
     */
    void IncrementMinor();
    /**
     * @brief Increment the Patch version number set and build number to zero
     *
     */
    void IncrementPatch();
    /**
     * @brief Increment the Build version number
     *
     */
    void IncrementBuild();

    unsigned int getMajor() const;
    unsigned int getMinor() const;
    unsigned int getPatch() const;
    unsigned int getBuild() const;
    bool isValid()
    {
        return _version[ VERSION::MAJOR ] > 0 ||
               _version[ VERSION::MINOR ] > 0 ||
               _version[ VERSION::PATCH ] > 0 ||
               _version[ VERSION::BUILD ] > 0;
    }

    ~Version();
};

#endif