#include "SpartaGameMode.h"
#include "SpartaCharacter.h"
#include "SpartaPawn.h"
#include "SpartaPlayerController.h"
#include "SpartaGameState.h"

ASpartaGameMode::ASpartaGameMode()
{
	// DefaultPawnClass = ASpartaPawn::StaticClass();
	DefaultPawnClass = ASpartaCharacter::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
	GameStateClass = ASpartaGameState::StaticClass();
}
