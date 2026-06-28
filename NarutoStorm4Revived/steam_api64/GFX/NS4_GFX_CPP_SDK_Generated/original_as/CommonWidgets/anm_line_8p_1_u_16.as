package freebtl_tonmt_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol34")]
   public dynamic class anm_line_8p_1_u_16 extends MovieClip
   {
      
      public function anm_line_8p_1_u_16()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,9,this.frame10,17,this.frame18,28,this.frame29);
      }
      
      internal function frame1() : *
      {
         stop();
      }
      
      internal function frame2() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MAKIMONO_OPEN2);
      }
      
      internal function frame10() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MAKIMONO_OPEN2);
      }
      
      internal function frame18() : *
      {
         ExternalInterface.call("RequestPlaySE",SeId.CCD_SE_ID_MAKIMONO_OPEN2);
      }
      
      internal function frame29() : *
      {
         stop();
      }
   }
}

