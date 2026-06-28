package freebtl_tonmt_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol14")]
   public dynamic class anm_line_4p_1_u_22 extends MovieClip
   {
      
      public function anm_line_4p_1_u_22()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,9,this.frame10,17,this.frame18,26,this.frame27);
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
      
      internal function frame27() : *
      {
         stop();
      }
   }
}

