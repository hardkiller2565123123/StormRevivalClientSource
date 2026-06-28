package freebtl_tonmt_fla
{
   import SeIdList.SeId;
   import flash.display.MovieClip;
   import flash.external.ExternalInterface;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol11")]
   public dynamic class anm_line_4p_2_21 extends MovieClip
   {
      
      public function anm_line_4p_2_21()
      {
         super();
         addFrameScript(0,this.frame1,1,this.frame2,8,this.frame9);
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
         stop();
      }
   }
}

