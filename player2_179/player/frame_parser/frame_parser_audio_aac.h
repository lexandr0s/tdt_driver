/************************************************************************
COPYRIGHT (C) SGS-THOMSON Microelectronics 2007

Source file name : frame_parser_audio_aac.h
Author :           Adam

Definition of the frame parser audio aac class implementation for player 2.


Date        Modification                                    Name
----        ------------                                    --------
05-Jul-07   Created (from frame_parser_audio_mpeg.h)        Adam

************************************************************************/

#ifndef H_FRAME_PARSER_AUDIO_AAC
#define H_FRAME_PARSER_AUDIO_AAC

// /////////////////////////////////////////////////////////////////////
//
//	Include any component headers

#include "aac_audio.h"
#include "frame_parser_audio.h"

// /////////////////////////////////////////////////////////////////////////
//
// Locally defined structures
//

// /////////////////////////////////////////////////////////////////////////
//
// The class definition
//

class FrameParser_AudioAac_c : public FrameParser_Audio_c
{
private:

    // Data
    
    AacAudioParsedFrameHeader_t ParsedFrameHeader;
    
    AacAudioStreamParameters_t	*StreamParameters;
    AacAudioStreamParameters_t CurrentStreamParameters;
    AacAudioFrameParameters_t *FrameParameters;
    
    unsigned int NumHeaderUnplayableErrors; ///< Number of *consecutive* header unplaybable errors.
    bool isFirstFrame;

    // Functions

public:

    //
    // Constructor function
    //

    FrameParser_AudioAac_c( void );
    ~FrameParser_AudioAac_c( void );

    //
    // Overrides for component base class functions
    //

    FrameParserStatus_t   Reset(		void );

    //
    // FrameParser class functions
    //

    FrameParserStatus_t   RegisterOutputBufferRing(	Ring_t		Ring );

    //
    // Stream specific functions
    //

    FrameParserStatus_t   ReadHeaders( 					void );
    FrameParserStatus_t   ResetReferenceFrameList(			void );
    FrameParserStatus_t   PurgeQueuedPostDecodeParameterSettings(	void );
    FrameParserStatus_t   PrepareReferenceFrameList(			void );
    FrameParserStatus_t   ProcessQueuedPostDecodeParameterSettings(	void );
    FrameParserStatus_t   GeneratePostDecodeParameterSettings(		void );
    FrameParserStatus_t   UpdateReferenceFrameList(			void );

    FrameParserStatus_t   ProcessReverseDecodeUnsatisfiedReferenceStack(void );
    FrameParserStatus_t   ProcessReverseDecodeStack(			void );
    FrameParserStatus_t   PurgeReverseDecodeUnsatisfiedReferenceStack(	void );
    FrameParserStatus_t   PurgeReverseDecodeStack(			void );
    FrameParserStatus_t   TestForTrickModeFrameDrop(			void );

    static FrameParserStatus_t ParseFrameHeader( unsigned char *FrameHeader,
                                                 AacAudioParsedFrameHeader_t *ParsedFrameHeader,
                                                 int AvailableBytes, 
                                                 AacFrameParsingPurpose_t Action,
                                                 bool EnableHeaderUnplayableErrors = false );
    
    static FrameParserStatus_t ParseAudioMuxElementConfig( BitStreamClass_c * Bits,
                                                           unsigned int *     SamplingFrequency,
                                                           unsigned int *     SampleCount,
                                                           int                AvailableBytes,
                                                           AacFrameParsingPurpose_t Action );
};

#endif /* H_FRAME_PARSER_AUDIO_AAC */

