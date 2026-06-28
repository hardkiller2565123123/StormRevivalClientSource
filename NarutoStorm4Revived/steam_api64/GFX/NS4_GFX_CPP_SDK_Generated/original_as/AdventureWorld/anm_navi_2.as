package script.map_sm
{
   import flash.display.MovieClip;
   import script.icon_navi.nut_navi;
   
   [Embed(source="/_assets/assets.swf", symbol="symbol15")]
   public class anm_navi extends MovieClip
   {
      
      public var all_navi:nut_navi;
      
      private var m_navi:MovieClip = null;
      
      public function anm_navi()
      {
         super();
         this.m_navi = this["all_navi"];
         if(this.m_navi == null)
         {
            trace("Not Found Navi Symbol!");
         }
      }
      
      public function SetMainEventNavi() : *
      {
         if(this.m_navi)
         {
            this.m_navi.gotoAndStop("main");
         }
      }
      
      public function SetSubEventNavi() : *
      {
         if(this.m_navi)
         {
            this.m_navi.gotoAndStop("sab");
         }
      }
      
      public function SetMainSubEventNavi() : *
      {
         if(this.m_navi)
         {
            this.m_navi.gotoAndStop("main_sub");
         }
      }
      
      public function CheckChangeNavi(param1:Boolean, param2:Boolean) : *
      {
         if(this.m_navi)
         {
            visible = param1 || param2;
            if(param2 == true && param1 == true)
            {
               this.m_navi.gotoAndStop("main_sub");
            }
            else if(param2 == true)
            {
               this.m_navi.gotoAndStop("sab");
            }
            else if(param1 == true)
            {
               this.m_navi.gotoAndStop("main");
            }
         }
      }
   }
}

