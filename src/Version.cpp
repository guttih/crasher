#include "Version.h"

// assignment operator
Version & Version::operator=( const Version &rhs )
{

    set( rhs.getMajor(), rhs.getMinor(), rhs.getPatch(), rhs.getBuild() );

    return *this;
}

Version &Version::operator+=( const int &incrementBuild )
{
    setBuild( _version[ VERSION::BUILD ] = getBuild() + incrementBuild );
    return *this;
}

// Define prefix increment operator.
Version &Version::operator++()
{
    *this += 1;
    return *this;
}

// Define postfix increment operator.
Version Version::operator++( int incrementBuild )
{
    Version temp = *this;
    ++*this;
    return temp;
}
bool Version::operator==( const Version &rhs )
{
    return getMajor() == rhs.getMajor() &&
           getMinor() == rhs.getMinor() &&
           getPatch() == rhs.getPatch() &&
           getBuild() == rhs.getBuild();
}
bool Version::operator>( const Version &rhs )
{
    return getMajor() > rhs.getMajor() ||
           getMinor() > rhs.getMinor() ||
           getPatch() > rhs.getPatch() ||
           getBuild() > rhs.getBuild();
}
bool Version::operator<( const Version &rhs )
{
    return getMajor() < rhs.getMajor() ||
           getMinor() < rhs.getMinor() ||
           getPatch() < rhs.getPatch() ||
           getBuild() < rhs.getBuild();
}
bool Version::operator!=( const Version &rhs )
{
    return !( *this == rhs );
}
bool Version::operator>=( const Version &rhs )
{
    return *this > rhs || *this == rhs;
}
bool Version::operator<=( const Version &rhs )
{
    return *this < rhs || *this == rhs;
}
Version::Version( const char *version )
{
    if( version == nullptr || version[ 0 ] == '\0' )
        return;

    set( version );
}

void Version::set( const char *version )
{
    if( version == nullptr || version[ 0 ] == '\0' )
        return;

    set( 0, 0, 0, 0 );

    int i = -1, c;
    unsigned long val = 0;
    unsigned short valLen = 0;
    VERSION select = MAJOR;

    c = version[ 0 ];
    while( c >= '0' && c <= '9' )
    {
        if( valLen > MAX_UINT_STRING_LEN )
        {
            set( 0, 0, 0, 0 );
            return; // number too long;
        }
        c = version[ ++i ];
        if( c < '0' || c > '9' )
        {

            _version[ select ] = val;
            select = ( VERSION ) ( ( int ) ( select ) + 1 );

            if( c == '\0' || i > MAX_VERSION_STRING_LEN )
                return;

            val = 0;
            valLen = 0;
            c = version[ ++i ];
        }
        val = val * 10 + ( c - 48 );
        valLen++;
    }
    if( c != '\0' )
    {
        set( 0, 0, 0, 0 );
        return; // invalid version;
    }
}

Version::Version( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build )
{
    set( major, minor, patch, build );
}

Version::~Version()
{
    if( m_versionString )
    {
        delete[] m_versionString;
    }
}

const char *Version::itoa( unsigned int val, int base )
{

    static char buf[ 32 ] = { 0 };
    if( val == 0 )
    {
        buf[ 0 ] = '0';
        return buf;
    }
    else
    {
        int i = 30;

        for(; val && i; --i, val /= base )
            buf[ i ] = "0123456789abcdef"[ val % base ];
        return &buf[ i + 1 ];
    }
}

const char *Version::c_str( VERSION showLastZeroPos )
{
    if( !m_versionString )
    {
        m_versionString = new char[ MAX_VERSION_STRING_LEN ];
    }
    m_versionString[ 0 ] = '\0';

    unsigned int val, pos = -1;
    int lastSlot = VERSION::BUILD;
    if( _version[ VERSION::BUILD ] == 0 && showLastZeroPos < VERSION::BUILD )
    {
        lastSlot--;
        if( _version[ VERSION::PATCH ] == 0 && showLastZeroPos < VERSION::PATCH )
        {
            lastSlot--;
            if( _version[ VERSION::MINOR ] ==  0 && showLastZeroPos < VERSION::MINOR )
            {
                lastSlot--;
            }
        }
    }

    for( int ver = VERSION::MAJOR; ver <= lastSlot; ver++ )
    {
        val = _version[ ver ];

        const char *p = itoa( val, 10 );
        unsigned int i = 0;
        while( p[ i ] != '\0' )
        {
            m_versionString[ ++pos ] = p[ i++ ];
        }
        if( ver < lastSlot )
        {
            m_versionString[ ++pos ] = '.';
        }
    }
    m_versionString[ ++pos ] = '\0';

    return m_versionString;
}
void Version::set( unsigned int major, unsigned int minor, unsigned int patch, unsigned int build )
{
    _version[ VERSION::MAJOR ] = major;
    _version[ VERSION::MINOR ] = minor;
    _version[ VERSION::PATCH ] = patch;
    _version[ VERSION::BUILD ] = build;
    if( m_versionString )
        m_versionString[ 0 ] = '\0';
}

void Version::setMajor( unsigned int value )
{
    set( value, 0, 0, 0 );
}

void Version::setMinor( unsigned int value )
{
    set( getMajor(), value, 0, 0 );
}
void Version::setPatch( unsigned int value )
{
    set( getMajor(), getMinor(), value, 0 );
}
void Version::setBuild( unsigned int value )
{
    set( getMajor(), getMinor(), getPatch(), value );
}

unsigned int Version::getMajor() const
{
    return _version[ VERSION::MAJOR ];
}
unsigned int Version::getMinor() const
{
    return _version[ VERSION::MINOR ];
}
unsigned int Version::getPatch() const
{
    return _version[ VERSION::PATCH ];
}
unsigned int Version::getBuild() const
{
    return _version[ VERSION::BUILD ];
}

void Version::IncrementMajor()
{
    setMajor( _version[ VERSION::MAJOR ] = getMajor() + 1 );
}
void Version::IncrementMinor()
{
    setMinor( _version[ VERSION::MINOR ] = getMinor() + 1 );
}
void Version::IncrementPatch()
{
    setPatch( _version[ VERSION::PATCH ] = getPatch() + 1 );
}
void Version::IncrementBuild()
{
    setBuild( _version[ VERSION::BUILD ] = getBuild() + 1 );
}

Version Version::operator+( const int &incrementBuild )
{
    Version tmp( *this );
    tmp += incrementBuild;
    return tmp;
}