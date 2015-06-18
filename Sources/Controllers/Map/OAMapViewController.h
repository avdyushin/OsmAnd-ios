//
//  OAMapViewController.h
//  OsmAnd
//
//  Created by Alexey Pelykh on 7/18/13.
//  Copyright (c) 2013 OsmAnd. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "OACommonTypes.h"
#import "OAMapRendererViewProtocol.h"
#import "OAObservable.h"
#import <Reachability.h>
#import "OAAppSettings.h"
#import "OAPOIType.h"

#define kNotificationSetTargetPoint @"kNotificationSetTargetPoint"
#define kNotificationNoSymbolFound @"kNotificationNoSymbolFound"
#define kNotificationContextMarkerClicked @"kNotificationContextMarkerClicked"
#define kNotificationLayersConfigurationChanged @"kNotificationLayersConfigurationChanged"

#define kCorrectionMinLeftSpace 40.0
#define kCorrectionMinBottomSpace 40.0

#if defined(OSMAND_IOS_DEV)
typedef NS_ENUM(NSInteger, OAVisualMetricsMode)
{
    OAVisualMetricsModeOff = 0,
    OAVisualMetricsModeBinaryMapData,
    OAVisualMetricsModeBinaryMapPrimitives,
    OAVisualMetricsModeBinaryMapRasterize
};
#endif // defined(OSMAND_IOS_DEV)

typedef NS_ENUM(NSInteger, OAMapSymbolType)
{
    OAMapSymbolUndefined = 0,
    OAMapSymbolContext,
    OAMapSymbolMyLocation,
    OAMapSymbolDestination,
    OAMapSymbolFavorite,
    OAMapSymbolPOI,
    OAMapSymbolLocation,
    OAMapSymbolWpt,
};

@interface OAMapSymbol : NSObject

@property (nonatomic) CLLocationCoordinate2D location;
@property (nonatomic) CGPoint touchPoint;
@property (nonatomic) OAPOIType *poiType;
@property (nonatomic) UIImage *icon;
@property (nonatomic) NSString *caption;
@property (nonatomic) NSString *captionExt;
@property (nonatomic) NSString *buildingNumber;
@property (nonatomic) OAMapSymbolType type;
@property (nonatomic) NSInteger sortIndex;

@property (nonatomic) NSString *phone;
@property (nonatomic) NSString *openingHours;
@property (nonatomic) NSString *url;
@property (nonatomic) NSString *desc;

@property (nonatomic) NSString *oper;
@property (nonatomic) NSString *brand;
@property (nonatomic) NSString *wheelchair;
@property (nonatomic) NSArray *fuelTags;

@end


@class OAGpxWpt;

@interface OAMapViewController : UIViewController <UIGestureRecognizerDelegate>

@property(weak, readonly) id<OAMapRendererViewProtocol> mapRendererView;
@property(readonly) OAObservable* stateObservable;
@property(readonly) OAObservable* settingsObservable;

@property(readonly) OAObservable* azimuthObservable;
- (void)animatedAlignAzimuthToNorth;

@property(readonly) OAObservable* zoomObservable;
@property(readonly) OAObservable* mapObservable;

@property (nonatomic) OAGpxWpt *foundWpt;
@property (nonatomic) NSArray *foundWptGroups;
@property (nonatomic) NSString *foundWptDocPath;


- (BOOL)findWpt:(CLLocationCoordinate2D)location;
- (BOOL)deleteFoundWpt;
- (BOOL)saveFoundWpt;
- (BOOL)addNewWpt:(OAGpxWpt *)wpt gpxFileName:(NSString *)gpxFileName;

- (BOOL)canZoomIn;
- (void)animatedZoomIn;
- (BOOL)canZoomOut;
- (void)animatedZoomOut;

- (void)goToPosition:(Point31)position31
            animated:(BOOL)animated;
- (void)goToPosition:(Point31)position31
             andZoom:(CGFloat)zoom
            animated:(BOOL)animated;

- (void)correctPosition:(Point31)targetPosition31
       originalCenter31:(Point31)originalCenter31
              leftInset:(CGFloat)leftInset
            bottomInset:(CGFloat)bottomInset
               animated:(BOOL)animated;

- (float)calculateMapRuler;

- (BOOL)isMyLocationVisible;

- (void)showContextPinMarker:(double)latitude longitude:(double)longitude animated:(BOOL)animated;
- (void)hideContextPinMarker;

- (void)postTargetNotification:(OAMapSymbol *)symbol;

- (void)simulateContextMenuPress:(UIGestureRecognizer*)recognizer;

- (void)showTempGpxTrack:(NSString *)fileName;
- (void)hideTempGpxTrack;
- (void)keepTempGpxTrackVisible;

- (void)showRecGpxTrack;
- (void)hideRecGpxTrack;

- (void)addDestinationPin:(NSString *)markerResourceName color:(UIColor *)color latitude:(double)latitude longitude:(double)longitude;
- (void)removeDestinationPin:(UIColor *)color;

@property(readonly) CGFloat displayDensityFactor;

@property(readonly) OAObservable* framePreparedObservable;

@property(nonatomic, assign) BOOL minimap;

#if defined(OSMAND_IOS_DEV)
@property(nonatomic) BOOL hideStaticSymbols;
@property(nonatomic) OAVisualMetricsMode visualMetricsMode;

@property(nonatomic) BOOL forceDisplayDensityFactor;
@property(nonatomic) CGFloat forcedDisplayDensityFactor;
#endif // defined(OSMAND_IOS_DEV)

@end
