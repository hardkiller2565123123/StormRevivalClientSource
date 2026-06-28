package freebtl_tonmt_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol31")]
   public dynamic class anm_line_8p_2_15 extends MovieClip
   {
      
      public function anm_line_8p_2_15()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,8,this.frame9,17,this.frame18);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MAKIMONO_OPEN2);
      }
      
      internal function frame9() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MAKIMONO_OPEN2);
      }
      
      internal function frame18() : *
      {
         stop();
      }
   }
}

