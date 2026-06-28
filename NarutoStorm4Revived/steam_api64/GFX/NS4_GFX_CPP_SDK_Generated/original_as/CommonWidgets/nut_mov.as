package script.hist_mov
{
   import ELoader.ExtendLoader;
   import flash.display.MovieClip;
   import flash.external.*;
   import flash.net.URLRequest;
   import script.xcmn_tex00.nut_tex00;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol7")]
   public class nut_mov extends MovieClip
   {
      
      public var dmy_msg2:nut_tex00;
      
      public var dmy_msg1:nut_tex00;
      
      private var m_titleDmyMC:MovieClip;
      
      private var m_endDmyMC:MovieClip;
      
      private var m_titleLoader:ExtendLoader;
      
      private var m_endLoader:ExtendLoader;
      
      public function nut_mov()
      {
         super();
         addFrameScript(0,this.frame1,29,this.frame30,60,this.frame61,90,this.frame91,120,this.frame121);
         this.m_titleDmyMC = this["dmy_msg1"];
         this.m_endDmyMC = this["dmy_msg2"];
         this.m_titleLoader = new ExtendLoader();
         this.m_endLoader = new ExtendLoader();
         this.m_titleLoader.SetPivot(ExtendLoader.CCD_PIVOT_TOP_LEFT);
         this.m_endLoader.SetPivot(ExtendLoader.CCD_PIVOT_BOTTOM_RIGHT);
         this.m_titleDmyMC.addChild(this.m_titleLoader);
         this.m_endDmyMC.addChild(this.m_endLoader);
      }
      
      public function LoadTitle(param1:String) : *
      {
         var _loc2_:URLRequest = new URLRequest(param1);
         this.m_titleLoader.unload();
         this.m_titleLoader.load(_loc2_);
      }
      
      public function LoadEnd(param1:String) : *
      {
         var _loc2_:URLRequest = new URLRequest(param1);
         this.m_endLoader.unload();
         this.m_endLoader.load(_loc2_);
      }
      
      internal function frame1() : *
      {
      }
      
      internal function frame30() : *
      {
         this.stop();
      }
      
      internal function frame61() : *
      {
         this.stop();
      }
      
      internal function frame91() : *
      {
         this.stop();
      }
      
      internal function frame121() : *
      {
         this.stop();
      }
   }
}

