package script.map_sm
{
   import flash.geom.Point;
   import flash.utils.Dictionary;
   
   internal class SingleMiddleMapParam
   {
      
      public var m_stageLeftTopPointList:Dictionary = new Dictionary();
      
      public var m_stageRightBottomPointList:Dictionary = new Dictionary();
      
      public var m_stageCode:String = "";
      
      public function SingleMiddleMapParam()
      {
         super();
         this.m_stageLeftTopPointList["sd13a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sa15a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd16a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["si51f"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["si35a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd07a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd01d"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd03a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["si00a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd17a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sd08a"] = new Point(-5000,5000);
         this.m_stageLeftTopPointList["sa71a"] = new Point(-5000,5000);
         this.m_stageRightBottomPointList["sd13a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sa15a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd16a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["si51f"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["si35a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd07a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd01d"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd03a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["si00a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd17a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sd08a"] = new Point(5000,-5000);
         this.m_stageRightBottomPointList["sa71a"] = new Point(5000,-5000);
      }
   }
}

