#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class TUTORIALPRACTICE_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ASpartaPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* LookAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Input")
	UInputAction* SprintAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> HUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* HUDWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu|Main")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu|Main")
	UUserWidget* MainMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu|GameOver")
	TSubclassOf<UUserWidget> GameOverMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu|GameOver")
	UUserWidget* GameOverMenuWidgetInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Menu|Fade")
	TSubclassOf<UUserWidget> FadeInAndOutWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Menu|Fade")
	UUserWidget* FadeInAndOutWidgetInstance;

	UFUNCTION(BlueprintPure, Category = "HUD")
	UUserWidget* GetHUDWidget() const;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, Category = "Menu|GameOver")
	void ShowGameOverMenu();
	UFUNCTION(BlueprintCallable, Category = "FadeInAndOut")
	void ShowFadeInAndOut();
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void StartGame(int32 LevelIndex);
	UFUNCTION(BlueprintCallable, Category = "Menu|Main")
	void QuitGame();
	UFUNCTION(BlueprintCallable, Category = "Menu|GameOver")
	void ReStartGame();

	virtual void BeginPlay() override;
};
