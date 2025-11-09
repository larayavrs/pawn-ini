/*
 * pawn-ini Example
 * 
 * This example demonstrates how to use the pawn-ini plugin
 * to read and write INI files from any location on the filesystem
 * without scriptfiles restrictions.
 */

#include <a_samp>
#include <pawn-ini>

public OnGameModeInit()
{
    print("\n========================================");
    print("pawn-ini - Usage Examples");
    print("========================================\n");
    
    // Example 1: Windows absolute path
    Example_WindowsAbsolutePath();
    
    // Example 2: Relative path
    Example_RelativePath();
    
    // Example 3: Player database
    Example_PlayerDatabase();
    
    return 1;
}

// ============================================================================
// EXAMPLE 1: Windows Absolute Path
// ============================================================================
Example_WindowsAbsolutePath()
{
    print("=== Example 1: Windows Absolute Path ===");
    
    new INI:config = INI_Open("C:/GameServers/SAMP/config.ini");
    
    if(config != INVALID_INI_HANDLE)
    {
        // Write server configuration
        INI_WriteString(config, "Server", "hostname", "Test Server");
        INI_WriteInt(config, "Server", "maxplayers", 50);
        INI_WriteFloat(config, "Server", "gravity", 0.008);
        INI_WriteString(config, "Server", "weburl", "www.example.com");
        
        // Read and display values
        new hostname[128];
        INI_ReadString(config, "Server", "hostname", hostname);
        printf("Hostname: %s", hostname);
        
        new maxplayers = INI_ReadInt(config, "Server", "maxplayers");
        printf("Max Players: %d", maxplayers);
        
        new Float:gravity = INI_ReadFloat(config, "Server", "gravity");
        printf("Gravity: %.3f", gravity);
        
        INI_Close(config);
        print("File saved successfully\n");
    }
    else
    {
        print("ERROR: Could not create/open file\n");
    }
}

// ============================================================================
// EXAMPLE 2: Relative Path
// ============================================================================
Example_RelativePath()
{
    print("=== Example 2: Relative Path ===");
    
    // "../configs" = parent folder + configs subfolder
    new INI:settings = INI_Open("../configs/settings.ini");
    
    if(settings != INVALID_INI_HANDLE)
    {
        // World configuration
        INI_WriteFloat(settings, "World", "weather_change_time", 600.0);
        INI_WriteInt(settings, "World", "default_weather", 10);
        INI_WriteInt(settings, "World", "enable_stuntbonus", 1);
        
        // Chat configuration
        INI_WriteInt(settings, "Chat", "max_message_length", 128);
        INI_WriteInt(settings, "Chat", "spam_protection", 1);
        INI_WriteFloat(settings, "Chat", "spam_interval", 0.5);
        
        // Check if section exists
        if(INI_SectionExists(settings, "World"))
        {
            print("'World' section exists");
        }
        
        // Check if key exists
        if(INI_KeyExists(settings, "Chat", "spam_protection"))
        {
            print("'spam_protection' key exists in 'Chat'");
        }
        
        INI_Close(settings);
        print("Settings saved\n");
    }
}

// ============================================================================
// EXAMPLE 3: Player Database
// ============================================================================
Example_PlayerDatabase()
{
    print("=== Example 3: Player Database ===");
    
    new INI:playerdb = INI_Open("C:/SAMP/users/players.ini");
    
    if(playerdb != INVALID_INI_HANDLE)
    {
        // Create sample players
        CreateSamplePlayer(playerdb, "John123");
        CreateSamplePlayer(playerdb, "Mary456");
        CreateSamplePlayer(playerdb, "Bob789");
        
        // Read player data
        print("\n--- Data for player John123 ---");
        ShowPlayerData(playerdb, "John123");
        
        // Update stats
        INI_WriteInt(playerdb, "John123", "score", 1500);
        INI_WriteInt(playerdb, "John123", "kills", 50);
        
        // Delete a player
        if(INI_SectionExists(playerdb, "Bob789"))
        {
            INI_DeleteSection(playerdb, "Bob789");
            print("\nPlayer Bob789 deleted");
        }
        
        // Delete a specific key
        INI_DeleteKey(playerdb, "Mary456", "admin_level");
        
        INI_Close(playerdb);
        print("Database closed successfully\n");
    }
}

CreateSamplePlayer(INI:handle, const name[])
{
    INI_WriteString(handle, name, "password", "hash_123456");
    INI_WriteInt(handle, name, "score", 0);
    INI_WriteInt(handle, name, "money", 5000);
    INI_WriteInt(handle, name, "kills", 0);
    INI_WriteInt(handle, name, "deaths", 0);
    INI_WriteInt(handle, name, "admin_level", 0);
    INI_WriteFloat(handle, name, "pos_x", 0.0);
    INI_WriteFloat(handle, name, "pos_y", 0.0);
    INI_WriteFloat(handle, name, "pos_z", 0.0);
    
    printf("Player '%s' created", name);
}

ShowPlayerData(INI:handle, const name[])
{
    if(!INI_SectionExists(handle, name))
    {
        printf("Player '%s' doesn't exist", name);
        return;
    }
    
    new score = INI_ReadInt(handle, name, "score");
    new money = INI_ReadInt(handle, name, "money");
    new kills = INI_ReadInt(handle, name, "kills");
    new deaths = INI_ReadInt(handle, name, "deaths");
    
    printf("Score: %d", score);
    printf("Money: $%d", money);
    printf("K/D: %d/%d", kills, deaths);
}

// ============================================================================
// EXAMPLE 4: Connection Logging (outside scriptfiles)
// ============================================================================
public OnPlayerConnect(playerid)
{
    // Save connection log outside scriptfiles
    new INI:log = INI_Open("C:/Logs/SAMP/connections.ini");
    
    if(log != INVALID_INI_HANDLE)
    {
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));
        
        new year, month, day, hour, minute, second;
        getdate(year, month, day);
        gettime(hour, minute, second);
        
        new timestamp[64];
        format(timestamp, sizeof(timestamp), "%02d/%02d/%d %02d:%02d:%02d", 
            day, month, year, hour, minute, second);
        
        INI_WriteString(log, name, "last_connect", timestamp);
        INI_WriteInt(log, name, "total_connections", 
            INI_ReadInt(log, name, "total_connections", 0) + 1);
        
        INI_Close(log);
    }
    
    return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
    // Save playtime stats
    new INI:stats = INI_Open("C:/SAMP/stats/playtime.ini");
    
    if(stats != INVALID_INI_HANDLE)
    {
        new name[MAX_PLAYER_NAME];
        GetPlayerName(playerid, name, sizeof(name));
        
        // Increment playtime (simplified example)
        new playtime = INI_ReadInt(stats, name, "total_minutes", 0);
        INI_WriteInt(stats, name, "total_minutes", playtime + 30);
        
        INI_Close(stats);
    }
    
    return 1;
}
