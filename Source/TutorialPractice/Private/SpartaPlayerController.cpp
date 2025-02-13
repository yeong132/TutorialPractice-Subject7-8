#include "SpartaPlayerController.h"
#include "SpartaGameState.h"
#include "SpartaGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

ASpartaPlayerController::ASpartaPlayerController() 
	: InputMappingContext(nullptr),
	  MoveAction(nullptr),
	  JumpAction(nullptr),
	  LookAction(nullptr),
	  SprintAction(nullptr),
	  HUDWidgetClass(nullptr),
	  HUDWidgetInstance(nullptr),
	  MainMenuWidgetClass(nullptr),
	  MainMenuWidgetInstance(nullptr),
	  GameOverMenuWidgetClass(nullptr),
	  GameOverMenuWidgetInstance(nullptr),
	  FadeInAndOutWidgetClass(nullptr),
	  FadeInAndOutWidgetInstance(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
	
	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu();
	}
}

UUserWidget* ASpartaPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void ASpartaPlayerController::ShowMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("MainMenu gogo"));
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromViewport();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (GameOverMenuWidgetInstance)
	{
		GameOverMenuWidgetInstance->RemoveFromParent();
		GameOverMenuWidgetInstance = nullptr;
	}

	if (FadeInAndOutWidgetInstance)
	{
		FadeInAndOutWidgetInstance->RemoveFromParent();
		FadeInAndOutWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		/*if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))
		{
			ButtonText->SetText(FText::FromString(TEXT("Start")));
		}*/

		/*if (bIsRestart)
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(
						FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)
					));
				}
			}
		}*/
		
	}
}

void ASpartaPlayerController::ShowGameOverMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("gameOver gogo"));
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (GameOverMenuWidgetInstance)
	{
		GameOverMenuWidgetInstance->RemoveFromParent();
		GameOverMenuWidgetInstance = nullptr;
	}

	if (FadeInAndOutWidgetInstance)
	{
		FadeInAndOutWidgetInstance->RemoveFromParent();
		FadeInAndOutWidgetInstance = nullptr;
	}

	if (GameOverMenuWidgetClass)
	{
		GameOverMenuWidgetInstance = CreateWidget<UUserWidget>(this, GameOverMenuWidgetClass);
		if (GameOverMenuWidgetInstance)
		{
			GameOverMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		UFunction* PlayAnimFunc = GameOverMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
		if (PlayAnimFunc)
		{
			GameOverMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
		}

		if (UTextBlock* TotalScoreText = Cast<UTextBlock>(GameOverMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
		{
			if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
			{
				TotalScoreText->SetText(FText::FromString(
					FString::Printf(TEXT("Total Score: %d"), SpartaGameInstance->TotalScore)
				));
			}
		}

		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if (SpartaGameState)
		{
			if (UTextBlock* GameOverText = Cast<UTextBlock>(GameOverMenuWidgetInstance->GetWidgetFromName("GameOverText")))
			{
				if (SpartaGameState->bIsGameCleared)
				{
					GameOverText->SetText(FText::FromString(FString::Printf(TEXT("Game Clear!!"))));
				}
				else
				{
					GameOverText->SetText(FText::FromString(FString::Printf(TEXT("Game Over..."))));
				}
			}
		}
	}
}

void ASpartaPlayerController::ShowFadeInAndOut()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (GameOverMenuWidgetInstance)
	{
		GameOverMenuWidgetInstance->RemoveFromParent();
		GameOverMenuWidgetInstance = nullptr;
	}

	if (FadeInAndOutWidgetInstance)
	{
		FadeInAndOutWidgetInstance->RemoveFromParent();
		FadeInAndOutWidgetInstance = nullptr;
		UE_LOG(LogTemp, Warning, TEXT("fade In chogihwa"));
	}

	if (FadeInAndOutWidgetClass)
	{
		FadeInAndOutWidgetInstance = CreateWidget<UUserWidget>(this, FadeInAndOutWidgetClass);
		if (FadeInAndOutWidgetInstance)
		{
			FadeInAndOutWidgetInstance->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("fade In gogo"));
			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		UFunction* FadeInFunc = FadeInAndOutWidgetInstance->FindFunction(FName("FadeInAnimFunction"));
		if (FadeInFunc)
		{
			FadeInAndOutWidgetInstance->ProcessEvent(FadeInFunc, nullptr);
		}
	}
}

void ASpartaPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
		if (SpartaGameState)
		{
			SpartaGameState->UpdateHUD();
		}
	}
}

void ASpartaPlayerController::StartGame(int32 LevelIndex)
{
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			SpartaGameInstance->TotalScore = 0;
			SpartaGameInstance->CurrentLevelIndex = LevelIndex;
			UGameplayStatics::OpenLevel(GetWorld(), SpartaGameState->LevelMapNames[LevelIndex]);
		}
	}

	SetPause(false);
}

void ASpartaPlayerController::ReStartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("ReStartGame() gogo"));
	ASpartaGameState* SpartaGameState = GetWorld() ? GetWorld()->GetGameState<ASpartaGameState>() : nullptr;
	if (SpartaGameState)
	{
		if (USpartaGameInstance* SpartaGameInstance = Cast<USpartaGameInstance>(UGameplayStatics::GetGameInstance(this)))
		{
			SpartaGameInstance->TotalScore = 0;
			SpartaGameInstance->CurrentLevelIndex = 0;
			UGameplayStatics::OpenLevel(GetWorld(), SpartaGameState->LevelMapNames[0]);
		}
	}
	SetPause(false);
}

void ASpartaPlayerController::QuitGame()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World ? World->GetFirstPlayerController() : nullptr;

	if (PlayerController)
	{
		UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, true);
	}
}