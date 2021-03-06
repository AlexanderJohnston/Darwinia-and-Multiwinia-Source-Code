#ifndef _included_taskmanagerinterfaceicons_h
#define _included_taskmanagerinterfaceicons_h

#include "lib/tosser/llist.h"
#include "worldobject/entity.h"
#include "worldobject/worldobject.h"
#include "taskmanager_interface.h"

class QuickUnitButton;

#define NUM_TASKMANAGER_ICONS_PARTICLES 256

class TaskManagerParticle
{
public:
	float alpha;
	float size;
	Vector2 speed;
	Vector2 pos;

	TaskManagerParticle()
	:	alpha(0.0f),
		size(0.0f)
	{
		speed = Vector2(0.0f,0.0f);
		pos = Vector2(0.0f,0.0f);
	}
};

class TaskManagerInterfaceIcons : public TaskManagerInterface
{
protected:
    enum
    {
        ScreenOverlay,                  // On all screens
        ScreenTaskManager,
        ScreenObjectives,
        ScreenResearch
    };
    int     m_screenId;
    
    float   m_screenY;
    float   m_desiredScreenY;
    float   m_screenW;
    float   m_screenH;

    float   m_chatLogY;
	
    LList   <ScreenZone *>          m_screenZones;               // All clickable areas on-screen
    LList   <ScreenZone *>          m_newScreenZones;            // New zones generated this frame
	LList   <KeyboardShortcut *>    m_keyboardShortcuts;         // Keyboard shortcuts to screenzones
    int     m_currentScreenZone;
    int     m_currentMouseScreenZone;
	int		m_currentScrollZone;
    float   m_screenZoneTimer;
    double  m_taskManagerDownTime;

	bool					*m_objectivesChanged;
	TaskManagerParticle		m_objectiveParticles[256];
	LList   <UnicodeString*>	m_progressBarList;
	bool					m_progressBarCompleted[256];
	float					m_progressBarFontSize;
	float					m_progressBarLongestStrSize;
	int						m_currentParticlesIndex;

protected:
    void    AdvanceScrolling            ();
    void    AdvanceScreenEdges          ();
    void    AdvanceScreenZones          ();    
    void    AdvanceKeyboardShortcuts    ();
    void    AdvanceTerminate            ();
	void	AdvanceProgressBar			();
    
    void    HideTaskManager             ();
    
    bool    ScreenZoneHighlighted   ( ScreenZone *_zone );
    void    RunScreenZone           ( const char *_name, int _data );          // Occurs during click or keypress

    void    SetupRenderMatrices     ( int _screenId );
    void    ConvertMousePosition    ( float &_x, float &_y );
    void    RestoreRenderMatrices   ();

    void    RenderTargetAreas   ();
    void    RenderMessages      ();
    void    RenderGestures      ();
    void    RenderRunningTasks  ();
    void    RenderOverview      ();
    void    RenderTaskManager   ();
    void    RenderObjectives    ();
    void    RenderResearch      ();
    void    RenderTitleBar      ();    
    void    RenderScreenZones   ();
    void    RenderTooltip       ();
    void    RenderCreateTaskMenu();
	void	RenderProgressBar	();
	
    void    RenderCompass       ( float _screenX, float _screenY, 
                                  Vector3 const &_worldPos, bool selected, float _size );

	bool	ButtonHeld();
	bool	ButtonHeldAndReleased();

	void	InitProgressBarList	();
	void	EvaluteTutorialObjectives	();
        
public:
    TaskManagerInterfaceIcons();
	~TaskManagerInterfaceIcons();

    virtual void Advance();        
    virtual void Render();

	bool ControlEvent( TMControl _type );
	bool AdviseCreateControlHelpBlue();
	bool AdviseCreateControlHelpGreen();
	bool AdviseCloseControlHelp();
	bool AdviseOverSelectableZone();
};

#endif
